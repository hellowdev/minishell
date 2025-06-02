/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:12:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 00:47:07 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_child(t_parce **data, t_child *pack)
{
	int	track;
	int	i_fork;

	if (built_in(*data, pack->env) == 1)
		return ;
	pack->i = 0;
	track = 0;
	i_fork = fork();
	if (i_fork == 0)
	{
		pack->check = 0;
		track = i_child(*data, -1, NULL, pack);
		free_doublst(data);
		exit(track);
	}
	signal(SIGINT, SIG_IGN);
	wait(&status);
	if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	else
		status = WEXITSTATUS(status);
}

void	first_child(t_parce **data, t_child *pack)
{
	int	track;

	track = 0;
	pack->i = 0;
	pack->ids[0] = fork();
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
		if (pack->ids[pack->i] == 0)
		{
			pack->check = 1;
			track = i_child(*data, oldtmp, pack->newpipe, pack);
			free_doublst(data);
			exit(track);
		}
		pack->i++;
		close(pack->newpipe[1]);
		close(oldtmp);
		oldtmp = pack->newpipe[0];
		(*data) = (*data)->next;
	}
	return (oldtmp);
}

void	last_child(t_parce **data, int oldtmp, t_child *pack)
{
	int	track;

	track = 0;
	pack->ids[pack->i] = fork();
	if (pack->ids[pack->i] == 0)
	{
		pack->check = 1;
		track = i_child(*data, oldtmp, NULL, pack);
		free_doublst(data);
		exit(track);
	}
	close(oldtmp);
}
