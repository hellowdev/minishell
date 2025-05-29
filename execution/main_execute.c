/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:18:45 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/29 19:53:55 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_fd(char **fds)
{
	int cnt;

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
	// -------- HEREDOC --------- //
	if (dup_heredoc(data->heredoc, data->input, pack->i) == -1)
		return (fd_closer(oldpipe, pipefd), 1);
	// -------- INFILE --------- //
	if (dup_infile(data->infiles, data->input) == -1)
		return (fd_closer(oldpipe, pipefd), 1);
	if (!data->heredoc && !data->infiles && pack->check == 1) // if not infile and not the first one
		dup2(oldpipe, 0);
	// -------- OUTFILE --------- //
	if (dup_outfile(data->outfiles, data->append) == -1)
		return (fd_closer(oldpipe, pipefd), 1);
	else if (!data->outfiles && data->next) // if not outfile and next node 
		dup2(pipefd[1], 1);
	// -------- CMD --------- //
	fd_closer(oldpipe, pipefd);
	// if cmd builtin -> execute with built_in_func and exit();
	if (built_in(data, pack->env, pack->status) == 1)
		exit(*pack->status);
	if (execute_cmd(data, *pack->env) == -1)
		return (127);
	return (0);
}

void	execute(t_parce *data, t_env **env, int *status)
{
	int newfd;
	t_child	pack;
	t_parce *tmp;

	tmp = data;
	if (heredoc(&data, *env, status) == 1)
		return (del_file(tmp));
	pack.env = env;
	pack.status = status;
	if (data->next == NULL) // one NODE
		return (one_child(&data, &pack), del_file(tmp));
	pipe(pack.pipefd);
	pack.ids = malloc(ft_lstsize(data) * sizeof(int));
	first_child(&data, &pack);
	data = data->next;

	newfd = listofchild(&data, &pack); // THE LIST OF NODE SEPARATE BY PIPE
	last_child(&data, newfd, &pack); // THE LAST NODE
	return (wait_proc(&pack), free(pack.ids), del_file(tmp));
}

void	wait_proc(t_child *pack)
{
	int i;

	i = 0;
	while (i <= pack->i)
	{
		signal(SIGINT, SIG_IGN); // bach nbdlo akhir signal d parent
		waitpid(pack->ids[i++], pack->status, 0);
	}
	if (WIFSIGNALED(*pack->status))
		*pack->status = WTERMSIG(*pack->status) + 128;
	else
		*pack->status = WEXITSTATUS(*pack->status);
}
