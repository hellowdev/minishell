/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:32:57 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/29 11:36:55 by ychedmi          ###   ########.fr       */
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

int	one_doc(t_parce *data, t_expand *stock)
{
	int		i_fork;

	if (data->heredoc)
	{
		i_fork = fork();
		if (i_fork == 0)
		{
			signal(SIGINT, SIG_DFL);
			creat_file(data->heredoc, data->check_qt, 0, stock);
			exit(0);
		}
		signal(SIGINT, SIG_IGN);
		wait(stock->status);
		if (WIFSIGNALED(*stock->status))
		{
			// printf("sig value > %d\n", WTERMSIG(*stock->status));
			printf("sig value > %d\n", *stock->status);
			return (*stock->status = 1);
		}
	}
	return (*stock->status = 0);
}

int	listofdoc(t_parce **data, t_expand *stock)
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
				return (ft_putstr_fd("\n", 1), *stock->status = 1); // *stock->status = 1 in return
		}
		i++;
		(*data) = (*data)->next;
	}
	return (*stock->status = 0); // all line
}

int	heredoc(t_parce *data, t_env *env, int *status)
{
	t_expand stock;

	stock.env = env;
	stock.status = status;
	if (data->next == NULL) // one NODE
		return (one_doc(data, &stock));
	else // LIST OF NODE
		return (listofdoc(&data, &stock)); // return 
}
