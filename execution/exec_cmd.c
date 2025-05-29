/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:58:34 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/29 15:21:59 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	**wich_path(t_env *env)
{
	char	**mypath;

	mypath = NULL;
	char *path;
	path = env_searsh(env, "PATH");
	mypath = ft_split(path, ':');
	return (free_null(&path), mypath);
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

char	**double_env(t_env *env)
{
	char **ret;
	int i;

	i = 0;
	ret = malloc((ft_sizeenv(env) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (env)
	{
		ret[i] = ft_strjoin(ft_strdup(env->name_env), ft_strdup("="));
		ret[i] = ft_strjoin(ret[i], ft_strdup(env->value_env));
		env = env->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	execute_cmd(t_parce *data, t_env *testenv)
{
	char *path;
	
	char **tenv;
	tenv = NULL;
	tenv = double_env(testenv);
	
	if (data->cmd)
	{
		path = valid_path(testenv, data->cmd[0]);
		if (!path)
			return (doubfree(tenv), -1); // free here or free all in child?
		execve(path, data->cmd, tenv);
	}
	return (doubfree(tenv), tenv = NULL, 0);
}
