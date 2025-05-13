/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:12:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/13 18:51:13 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	i_child(t_parce *data, int *pipefd, int check)
{
	
	// -------- INFILE --------- //
	if (dup_infile(data->infiles) == -1) // if (infile)
		return (close(pipefd[0]), close(pipefd[1]), 1);
	else if (!data->infiles && check == 0) // if not infile and not the first one
		dup2(pipefd[0], 0);
	// -------- OUTFILE --------- //
	if(dup_outfile(data->outfiles, data->append) == -1) // if (outfile)
		return (close(pipefd[0]), close(pipefd[1]), 1);
	else if (!data->outfiles && data->next) // if not outfile and next node 
		dup2(pipefd[1], 1);
	// -------- CMD --------- //
	close(pipefd[1]);
	close(pipefd[0]);
	if (execute_cmd(data) == -1)
		return (127);
		// return (close(pipefd[0]), close(pipefd[1]), 127);
	// if (data->heredoc)
	return (0);
}

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
		track = i_child(data, pipefd, 1);
		// free
		printf("one in list\n");
		exit(track);
	}
	// waitpid(i_fork, status, 0);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(status);
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
		track = i_child(data, pipefd, 1);
		// printf("first in list\n");
		exit(track);
	}
	// waitpid(i_fork, status, 0);
	wait(status);
}

void	listofchild(t_parce **data, t_env *env, int *pipefd, int *status)
{
	(void)env;
	int i_fork;
	int track;

	track = 0;
	while ((*data)->next)
	{
		
		printf("list in while\n");
		i_fork = fork();
		if (i_fork == 0)
		{
			track = i_child(*data, pipefd, 0);
		}
		wait(status); // *status updated in the last_child func
		(*data) = (*data)->next;
	}
}

void	last_child(t_parce *data, t_env *env, int *pipefd, int *status)
{
	(void)env;
	int i_fork;
	int track;

	track = 0;
	i_fork = fork();
	if (i_fork == 0)
	{	
		track = i_child(data, pipefd, 0);
		printf("last in list\n");
		exit(track);
	}
	waitpid(i_fork, status, 0);
	// close(pipefd[0]);
	// close(pipefd[1]);
	*status = WEXITSTATUS(*status);
}
