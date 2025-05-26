/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:32:57 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/24 12:55:10 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_file(t_parce *nodes)
{
	int cnt;
	char *delfile;

	cnt = 0;
	while (nodes)
	{
		if (nodes->heredoc)
		{
			delfile = file_name(cnt);
			unlink(delfile);
			free_null(&delfile);
		}
		cnt++;
		nodes = nodes->next;
	}
}

void	one_doc(t_parce *data, t_expand *stock)
{
	int		i_fork;

	if (data->heredoc)
	{
		i_fork = fork();
		if (i_fork == 0)
		{
			creat_file(data->heredoc, data->check_qt, 0, stock);
			exit(0);
		}
		wait(NULL);
	}
}

void	listofdoc(t_parce **data, t_expand *stock)
{
	int i_fork;
	int i;

	i = 0;
	while ((*data))
	{
		if ((*data)->heredoc)
		{
			i_fork = fork();
			if (i_fork == 0)
			{
				creat_file((*data)->heredoc, (*data)->check_qt, i, stock);
				exit(0);
			}
			wait(NULL);
		}
		i++;
		(*data) = (*data)->next;
	}
}

void	heredoc(t_parce *data, t_env *env, int status)
{
	t_expand stock;

	stock.env = env;
	stock.status = status;
	if (data->next == NULL) // one NODE
		return (one_doc(data, &stock));
	else // LIST OF NODE
		listofdoc(&data, &stock);
}
