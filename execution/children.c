/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:12:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/11 17:44:03 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	i_child(t_parce *data)
{
	int j;

	j = 0;
	
	if (data->infiles)
	
		// dup infile
	if (data->outfiles)
		// dup outfile
		if (data->append)
	if (data->cmd)
		// execute the cmd
	if (data->heredoc)
	
}

void	one_child(t_parce *data, t_env *env)
{
	(void)env;
	int i_fork;
	// char *splited_path;
	i_fork = fork();
	if (i_fork == 0)
	{
		i_child(data);
		// splited_path = valid_path(environ, data->cmd[0]);
		// printf("> %s\n", splited_path);	
		printf("one in list\n");
		exit(1);
	}
}

void	first_child(t_parce *data, t_env *env)
{
	(void)env;
	int i_fork;
	char *splited_path;
	i_fork = fork();
	if (i_fork == 0)
	{
		splited_path = valid_path(environ, data->cmd[0]);
		printf("> %s\n", splited_path);
		// i_child();
		printf("first in list\n");
		exit(1);
	}
}

void	listofchild(t_parce **data, t_env *env, int *status)
{
	(void)env;
	int i_fork;
	char *splited_path;
	while ((*data)->next)
	{
		i_fork = fork();
		if (i_fork == 0)
		{
			splited_path = valid_path(environ, (*data)->cmd[0]);
			printf("> %s\n", splited_path);
			// i_child();
			printf("list in while\n");
		}
		wait(status);
		(*data) = (*data)->next;
	}
}

void	last_child(t_parce *data, t_env *env)
{
	(void)env;
	int i_fork;
	char *splited_path;
	i_fork = fork();
	if (i_fork == 0)
	{	
		splited_path = valid_path(environ, data->cmd[0]);
		printf("> %s\n", splited_path);	
		// i_child();
		printf("last in list\n");
		exit(1);
	}
}