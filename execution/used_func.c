/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   used_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:36:22 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/19 10:52:08 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int strlen_herdoc(char *s)
{
	int i;

	i = 1;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (i);	
}

int ft_strcm_doc(char *s1, char *s2)
{
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i] && s1[i] != '\n')
		i++;
	if (s1[i] == '\n')
	{
		i++;
		return (s1[i] - s2[i - 1]);
	}
	return (s1[i] - s2[i]);
}

void	fd_closer(int fd, int *pipefd)
{
	close(fd);
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	wait_proc(t_child *pack)
{
	int i;

	i = 0;
	while (i <= pack->i)
		waitpid(pack->ids[i++], pack->status, 0);
	*pack->status = WEXITSTATUS(*pack->status);
}

char	**split_path(char *env)
{
	char	**p;
	int		i;

	i = 0;
	while (env[i] != '/')
		i++;
	p = ft_split(&env[i], ':');
	if (!p)
		return (NULL);
	return (p);
}

char	**wich_path(char **env)
{
	int		t;
	char	**mypath;

	t = 0;
	mypath = NULL;
	while (env[t])
	{
		if (ft_strnstr(env[t], "PATH", 5))
		{
			mypath = split_path(env[t]);
			if (!mypath)
				return (NULL);
			break ;
		}
		t++;
	}
	return (mypath);
}

char	*valid_path(char **env, char *cmd)
{
	char	**p;
	char	*path;
	int		i;

	i = 0;
	p = wich_path(env);
	if (!p)
		return (NULL);
	if (access(cmd, F_OK & X_OK) == 0)
		return (doubfree(p), ft_strdup(cmd));
	while (p[i])
	{
		path = ft_slash_join(p[i], cmd);
		if (!path)
			return (doubfree(p), NULL);
		if (access(path, F_OK & X_OK) == 0)
			return (doubfree(p), path);
		free(path);
		i++;
	}
	doubfree(p);
	return (NULL);
}

int	count_fd(char **fds)
{
	int cnt;

	cnt = 0;
	while (fds[cnt])
		cnt++;
	return (cnt - 1);
}

int	redire_err(char *file, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
	return (-1);
}
