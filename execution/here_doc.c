/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:32:57 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/29 18:17:11 by ychedmi          ###   ########.fr       */
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

// int	one_doc(t_parce **data, t_expand *stock)
// {
// 	int		i_fork;

// 	if ((*data)->heredoc)
// 	{
// 		i_fork = fork();
// 		if (i_fork == 0)
// 		{
// 			signal(SIGINT, SIG_DFL);
// 			creat_file((*data)->heredoc, (*data)->check_qt, 0, stock);
// 			free_doublst(data);
// 			exit(0);
// 		}
// 		signal(SIGINT, SIG_IGN);
// 		wait(stock->status);
// 		if (WIFSIGNALED(*stock->status))
// 			return (ft_putstr_fd("\n", 1), *stock->status = 1);
// 	}
// 	*stock->status = WEXITSTATUS(*stock->status);
// 	return (0);
// }

int	listofdoc(t_parce **data, t_parce *tmp, t_expand *stock)
{
	int i_fork;
	int i;

	i = 0;
	while (tmp)
	{
		if (tmp->heredoc)
		{
			i_fork = fork();
			if (i_fork == 0)
			{
				signal(SIGINT, SIG_DFL);
				creat_file(tmp->heredoc, tmp->check_qt, i, stock);
				free_doublst(data);
				exit(0);
			}
			signal(SIGINT, SIG_IGN);
			wait(stock->status);
			if (WIFSIGNALED(*stock->status))
				return (ft_putstr_fd("\n", 1), *stock->status = 1);
		}
		i++;
		tmp = tmp->next;
	}
	return (*stock->status = WEXITSTATUS(*stock->status), 0);
}

int	heredoc(t_parce **data, t_env *env, int *status)
{
	t_expand stock;
	t_parce	 *tmp;

	tmp = *data;
	stock.env = env;
	stock.status = status;
	// if (tmp->next == NULL) // one NODE
	// 	return (one_doc(data, &stock));
	return (listofdoc(data, tmp, &stock)); // return
}
