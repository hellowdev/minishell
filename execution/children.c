/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:12:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/15 20:16:43 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	one_child(t_parce *data, t_env *env, int *pipefd, int *status)
{
	(void)env;
	(void)data;
	int track;
	int i_fork;

	track = 0;
	i_fork = fork();
	if (i_fork == 0)
	{
		track = i_child(data, pipefd[0], pipefd, 1);
		// free
		exit(track);
	}
	wait(status);
	close(pipefd[0]);
	close(pipefd[1]);
	*status = WEXITSTATUS(*status);
}

void	first_child(t_parce *data, t_child *pack)
{
	// int i_fork;
	int track;

	track = 0;
	pack->ids[0] = fork();
	if (pack->ids[0] == 0)
	{
		track = i_child(data, pack->pipefd[0], pack->pipefd, 1);
		exit(track);
	}
	close(pack->pipefd[1]);
	// wait(pack->status);
}

int	listofchild(t_parce **data, t_child *pack)
{
	int track;
	int oldtmp;

	oldtmp = pack->pipefd[0];
	track = 0;
	pack->i = 1;
	while ((*data)->next)
	{
		pipe(pack->newpipe);
		pack->ids[pack->i] = fork();
		if (pack->ids[pack->i] == 0)
		{
			track = i_child(*data, oldtmp, pack->newpipe, 0);
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

void	last_child(t_parce *data, int oldtmp, t_child *pack)
{
	int track;

	track = 0;
	pack->ids[pack->i] = fork();
	if (pack->ids[pack->i] == 0)
	{	
		track = i_child(data, oldtmp, NULL, 0);
		// printf("last in list\n");
		exit(track);
	}
	close(oldtmp);
}
