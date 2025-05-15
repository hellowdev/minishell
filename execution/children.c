/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:12:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/15 14:55:11 by ychedmi          ###   ########.fr       */
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

void	first_child(t_parce *data, t_env *env, int *pipefd, int *status)
{
	(void)env;
	int i_fork;
	int track;

	track = 0;
	i_fork = fork();
	if (i_fork == 0)
	{
		track = i_child(data, pipefd[0], pipefd, 1);
		// printf("first in list\n");
		exit(track);
	}
	close(pipefd[1]);
	// close(pipefd[0]);
	wait(status);
}

int	listofchild(t_parce **data, t_env *env, int *pipefd, int *status)
{
	(void)env;
	int i_fork;
	int track;
	int oldtmp;
	int newpipe[2];
	
	oldtmp = pipefd[0];
	track = 0;
	while ((*data)->next)
	{
		pipe(newpipe);
		i_fork = fork();
		if (i_fork == 0)
		{
			track = i_child(*data, oldtmp, newpipe, 0);
			exit(track);
		}
		wait(status); // *status updated in the last_child func
		close(newpipe[1]);
		close(oldtmp);
		oldtmp = newpipe[0];
		(*data) = (*data)->next;
	}
	return (oldtmp);
}

void	last_child(t_parce *data, t_env *env, int oldtmp, int *status)
{
	(void)env;
	int i_fork;
	int track;

	track = 0;
	i_fork = fork();
	if (i_fork == 0)
	{	
		track = i_child(data, oldtmp, NULL, 0);
		// printf("last in list\n");
		exit(track);
	}
	wait(status);
	close(oldtmp);
	*status = WEXITSTATUS(*status);
}
