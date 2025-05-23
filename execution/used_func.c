/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   used_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:36:22 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/23 18:51:17 by ychedmi          ###   ########.fr       */
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

char	**wich_path(t_env *env)
{
	int		t;
	char	**mypath;

	// (void)env;
	t = 0;
	mypath = NULL;
	char *path;
	path = env_searsh(env, "PATH");
	mypath = ft_split(path, ':');
	// mypath = split_path(env[t]);
	// if (!mypath)
	// 			return (NULL);
	// while (env[t])
	// {
	// 	if (ft_strnstr(env[t], "PATH", 5))
	// 	{
	// 		
	// 		break ;
	// 	}
	// 	t++;
	// }
	return (mypath);
}

int	is_slash(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*valid_path(t_env *env, char *cmd)
{
	char	**p;
	char	*path;
	int		i;

	i = 0;
	if (is_slash(cmd) == 1 && access(cmd, F_OK) != 0)
		return (redire_err(cmd, ": No such file or directory"), NULL);
	if (is_slash(cmd) == 1 && access(cmd, X_OK) != 0)
		return (redire_err(cmd, ": Permission denied"), NULL);
	if (is_slash(cmd) == 1 && access(cmd, F_OK & X_OK) == 0)
		return (ft_strdup(cmd));
	p = wich_path(env);
	if (!p)
		return (redire_err(cmd, ": No such file or directory"), doubfree(p), NULL);
	while (p[i])
	{
		path = ft_slash_join(p[i], cmd);
		if (!path)
			return (doubfree(p), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (doubfree(p), path);
		free(path);
		i++;
	}
	return (redire_err(cmd, ": command not found"), doubfree(p), NULL);
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
	if (err)
		write(2, "\n", 1);
	return (-1);
}
