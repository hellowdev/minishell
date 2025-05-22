/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:32:57 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/22 18:01:18 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_doc(t_parce *data, t_expand *stock)
{
	int		i_fork;

	i_fork = fork();
	if (i_fork == 0)
	{
		creat_file(data->heredoc, data->check_qt, 0, stock);
		exit(0);
	}
	wait(NULL);
}

void	first_doc(t_parce *data, t_expand *stock)
{
	int	i_fork;
	
	i_fork = fork();
	if (i_fork == 0)
	{
		creat_file(data->heredoc, data->check_qt, 0, stock);		
		exit(0);
	}
	wait(NULL);
}

int	listofdoc(t_parce **data, t_expand *stock)
{
	int i_fork;
	int i;

	i = 1;
	while ((*data)->next)
	{
		i_fork = fork();
		if (i_fork == 0)
		{
			creat_file((*data)->heredoc, (*data)->check_qt, i, stock);
			exit(0);
		}
		wait(NULL);
		i++;
		(*data) = (*data)->next;
	}
	return (i);
}

void	last_doc(t_parce *data, int *i, t_expand *stock)
{
	int i_fork;
	
	i_fork = fork();
	if (i_fork == 0)
	{	
		creat_file(data->heredoc, data->check_qt, *i, stock);	
		exit(0);
	}
	wait(NULL);
}

void	heredoc(t_parce *data, t_env *env, int status)
{
	int i;
	t_expand stock;

	stock.env = env;
	stock.status = status;
	if (data->next == NULL) // one NODE
		return (one_doc(data, &stock));
	else // FIRST NODE IN THE LIST
	{
		first_doc(data, &stock);
		data = data->next;
	}
	// THE LIST OF NODE SEPARATE BY PIPE
	i = listofdoc(&data, &stock);
	// THE LAST NODE
	last_doc(data, &i, &stock);
}