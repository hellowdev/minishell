/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:32:57 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/28 21:53:55 by ychedmi          ###   ########.fr       */
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

void disable_ctrl_echo() 
{
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ECHOCTL;  // Disable echoing of control characters
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void	one_doc(t_parce *data, t_expand *stock)
{
	int		i_fork;

	if (data->heredoc)
	{
		i_fork = fork();
		if (i_fork == 0)
		{
			signal(SIGINT, handle_doc_sig);
			creat_file(data->heredoc, data->check_qt, 0, stock);
			exit(0);
		}
		signal(SIGINT, SIG_IGN);
		wait(stock->status);
	// if (WIFSIGNALED(stock->status))
	// 	*stock->status = WTERMSIG(*stock->status);
	// else
	// 	*stock->status = WEXITSTATUS(*stock->status);
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
				signal(SIGINT, SIG_DFL);
				creat_file((*data)->heredoc, (*data)->check_qt, i, stock);
				exit(0);
			}
			signal(SIGINT, SIG_IGN);
			wait(stock->status);
			if (WIFSIGNALED(*stock->status))
				return ft_putstr_fd("\n", 1);
		}
		i++;
		(*data) = (*data)->next;
	}
}

void	heredoc(t_parce *data, t_env *env, int *status)
{
	t_expand stock;

	stock.env = env;
	stock.status = status;
	if (data->next == NULL) // one NODE
		return (one_doc(data, &stock));
	else // LIST OF NODE
		listofdoc(&data, &stock);
}
