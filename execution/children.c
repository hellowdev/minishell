/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:12:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/29 21:49:35 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fork_error(void)
{
	return (g_status = 1, ft_putstr_fd \
	("minishell: fork: Resource temporarily unavailable\n", 2));
}

void	one_child(t_parce **data, t_child *pack)
{
	int	track;
	int	i_fork;

	if (built_in(*data, pack->env) == 1)
		return ;
	pack->i = 0;
	track = 0;
	i_fork = fork();
	if (i_fork < 0)
		return (fork_error());
	if (i_fork == 0)
	{
		pack->check = 0;
		track = i_child(*data, -1, NULL, pack);
		free_doublst(data);
		exit(track);
	}
	signal(SIGINT, SIG_IGN);
	wait(&g_status);
	if (WIFSIGNALED(g_status))
		g_status = WTERMSIG(g_status) + 128;
	else
		g_status = WEXITSTATUS(g_status);
}

void	first_child(t_parce **data, t_child *pack)
{
	int	track;

	track = 0;
	pack->i = 0;
	pack->ids[0] = fork();
	if (pack->ids[0] < 0)
		return (fork_error());
	if (pack->ids[0] == 0)
	{
		pack->check = 0;
		track = i_child(*data, pack->pipefd[0], pack->pipefd, pack);
		free_doublst(data);
		exit(track);
	}
	close(pack->pipefd[1]);
}

int	listofchild(t_parce **data, t_child *pack)
{
	int	track;
	int	oldtmp;

	oldtmp = pack->pipefd[0];
	track = 0;
	pack->i = 1;
	while ((*data)->next)
	{
		pipe(pack->newpipe);
		pack->ids[pack->i] = fork();
		if (pack->ids[0] < 0)
			return (fork_error(), -1);
		if (pack->ids[pack->i] == 0)
		{
			pack->check = 1;
			track = i_child(*data, oldtmp, pack->newpipe, pack);
			free_doublst(data);
			exit(track);
		}
		close(pack->newpipe[1]);
		close(oldtmp);
		oldtmp = pack->newpipe[0];
		(*data) = (*data)->next;
		pack->i++;
	}
	return (oldtmp);
}

void	last_child(t_parce **data, int oldtmp, t_child *pack)
{
	int	track;

	track = 0;
	pack->ids[pack->i] = fork();
	if (pack->ids[pack->i] < 0)
		return (fork_error());
	if (pack->ids[pack->i] == 0)
	{
		pack->check = 1;
		track = i_child(*data, oldtmp, NULL, pack);
		free_doublst(data);
		exit(track);
	}
	close(oldtmp);
}
