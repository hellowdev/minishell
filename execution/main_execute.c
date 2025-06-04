/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:18:45 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/04 16:55:56 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_fd(char **fds)
{
	int	cnt;

	cnt = 0;
	while (fds[cnt])
		cnt++;
	return (cnt - 1);
}

void	fd_closer(int fd, int *pipefd)
{
	if (fd > 0)
		close(fd);
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

int	i_child(t_parce *data, int oldpipe, int *pipefd, t_child *pack)
{
	signal(SIGQUIT, SIG_DFL);
	if (dup_heredoc(data->heredoc, data->input, pack->i) == -1)
		return (fd_closer(oldpipe, pipefd), 1);
	if (dup_infile(data->infiles, data->input) == -1)
		return (fd_closer(oldpipe, pipefd), 1);
	if (!data->heredoc && !data->infiles \
	&& pack->check == 1)
		dup2(oldpipe, 0);
	if (dup_outfile(data->outfiles, data->append) == -1)
		return (fd_closer(oldpipe, pipefd), 1);
	else if (!data->outfiles && data->next) 
		dup2(pipefd[1], 1);
	fd_closer(oldpipe, pipefd);
	if (built_in(data, pack->env) == 1)
	{
		free_env(*pack->env);
		exit(g_status);
	}
	if (execute_cmd(data, *pack->env) == -1)
		return (free_env(*pack->env), g_status);
	return (0);
}

void	execute(t_parce *data, t_env **env)
{
	int		newfd;
	t_child	pack;
	t_parce	*tmp;

	tmp = data;
	if (heredoc(&data, env) == 1)
		return (del_file(tmp));
	pack.env = env;
	if (data->next == NULL)
		return (one_child(&data, &pack), del_file(tmp));
	pipe(pack.pipefd);
	pack.ids = malloc(ft_lstsize(data) * sizeof(int));
	first_child(&data, &pack);
	data = data->next;
	newfd = listofchild(&data, &pack);
	if (newfd != -1)
		last_child(&data, newfd, &pack);
	return (wait_proc(&pack), free(pack.ids), del_file(tmp));
}

void	wait_proc(t_child *pack)
{
	int	i;

	i = 0;
	while (i <= pack->i)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pack->ids[i++], &g_status, 0);
	}
	if (WIFSIGNALED(g_status))
	{
		if (WTERMSIG(g_status) == SIGPIPE)
		{
			g_status = 1;
			return ;
		}
		g_status = WTERMSIG(g_status) + 128;
	}
	else
		g_status = WEXITSTATUS(g_status);
}
