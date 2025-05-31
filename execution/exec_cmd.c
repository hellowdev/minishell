/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:58:34 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/30 19:16:25 by ychedmi          ###   ########.fr       */
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

char	*search_path(char *cmd, t_env *env)
{
	char	**env_path;
	char	*cmd_path;
	int		i;
	
	i = 0;
	env_path = wich_path(env);
	while (env_path && env_path[i])
	{
		cmd_path = ft_slash_join(env_path[i], cmd);
		if (!cmd_path)
			return (doubfree(env_path), NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (doubfree(env_path), cmd_path);
		free_null(&cmd_path);
		i++;
	}
	if (access(cmd, F_OK) != 0 && env_path)
		return (redire_err(cmd, ": command not found"), doubfree(env_path), NULL);
	if (access(cmd, F_OK) != 0 && !env_path)
		return (redire_err(cmd, ": No such file or directory"), NULL);
	if (access(cmd, X_OK) != 0)
		return (redire_err(cmd, ": Permission denied"), NULL);
	return (ft_strdup(cmd));
}

char	*valid_path(t_env *env, char *cmd)
{
	struct stat info;

	if (!*cmd)
		return (redire_err(cmd, ": command not found"), NULL);
	if (is_slash(cmd) && stat(cmd, &info) != 0)
		return (redire_err(cmd, ": No such file or directory"), NULL);
	if (S_ISDIR(info.st_mode))
		return (redire_err(cmd, ": is a directory"), NULL);
	if (is_slash(cmd) && access(cmd, F_OK & X_OK) == 0)
		return (ft_strdup(cmd));
	return (search_path(cmd, env));
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
	char	*path;
	char	**tenv;
	int		i;

	tenv = double_env(testenv);
	i = 0;
	if (data->cmd && *data->cmd)
	{
		path = valid_path(testenv, data->cmd[i]);
		if (!path)
			return (doubfree(tenv), -1);
		execve(path, data->cmd, tenv);
		free_null(&path);
	}
	return (doubfree(tenv), tenv = NULL, 0);
}
