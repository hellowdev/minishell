/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:12:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/27 20:08:41 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_child(t_parce *data, t_child *pack)
{
	// if (built_in(data->cmd, pack->env, pack->status) == 1)
	// 	return ;
	if (built_in(data, pack->env, pack->status) == 1)
	{
		close(pack->pipefd[0]);
		close(pack->pipefd[1]);
		return ;
	}
	int track;
	int i_fork;

	pack->i = 0;
	track = 0;
	i_fork = fork();
	if (i_fork == 0)
	{
		pack->check = 0;
		track = i_child(data, pack->pipefd[0], pack->pipefd, pack);
		// free
		exit(track);
	}
	wait(pack->status);
	close(pack->pipefd[0]);
	close(pack->pipefd[1]);
	*pack->status = WEXITSTATUS(*pack->status);
}

void	first_child(t_parce *data, t_child *pack)
{
	int track;

	track = 0;
	pack->i = 0;
	pack->ids[0] = fork();
	if (pack->ids[0] == 0)
	{
		pack->check = 0;
		track = i_child(data, pack->pipefd[0], pack->pipefd, pack);
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
			pack->check = 1;
			track = i_child(*data, oldtmp, pack->newpipe, pack);
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
		pack->check = 1;
		track = i_child(data, oldtmp, NULL, pack);
		exit(track);
	}
	close(oldtmp);
}
