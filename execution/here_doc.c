/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:32:57 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/04 09:56:32 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_file(t_parce *nodes)
{
	int		cnt;
	char	*delfile;

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

int	listofdoc(t_parce **data, t_parce *tmp, t_env *env, int i)
{
	int	i_fork;
	
	while (tmp)
	{
		if (tmp->heredoc)
		{
			i_fork = fork();
			if (i_fork == -1)
				return (perror("minishell: fork"), -1);
			if (i_fork == 0)
			{
				creat_file(tmp->heredoc, tmp->check_qt, i, env);
				free_doublst(data);
				exit(0);
			}
			signal(SIGINT, SIG_IGN);
			wait(&g_status);
			if (WIFSIGNALED(g_status))
				return (ft_putstr_fd("\n", 1), g_status = 1);
		}
		i++;
		tmp = tmp->next;
	}
	return (g_status = WEXITSTATUS(g_status), 0);
}

int	heredoc(t_parce **data, t_env *env)
{
	t_parce		*tmp;

	tmp = *data;
	return (listofdoc(data, tmp, env, 0));
}
