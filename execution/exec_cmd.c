/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:58:34 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/04 16:00:04 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**wich_path(t_env *env)
{
	char	**mypath;
	char	*path;

	mypath = NULL;
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
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (doubfree(env_path), cmd_path);
		free_null(&cmd_path);
		i++;
	}
	if (access(cmd, F_OK) != 0 && env_path)
		return (g_status = 127, redire_err(cmd, ": command not found"), \
		doubfree(env_path), NULL);
	if (access(cmd, F_OK) != 0 && !env_path)
		return (g_status = 127, \
		redire_err(cmd, ": No such file or directory"), NULL);
	if (access(cmd, X_OK) != 0)
		return (g_status = 126, \
		redire_err(cmd, ": Permission denied"), NULL);
	return (ft_strdup(cmd));
}

char	*valid_path(t_env *env, char *cmd)
{
	struct stat	info;

	if (!*cmd)
		return (g_status = 127, redire_err(cmd, ": command not found"), NULL);
	if (is_slash(cmd) && stat(cmd, &info) != 0)
		return (g_status = 127, \
		redire_err(cmd, ": No such file or directory"), NULL);
	if (S_ISDIR(info.st_mode))
		return (g_status = 126, redire_err(cmd, ": is a directory"), NULL);
	if (is_slash(cmd) && access(cmd, X_OK) != 0)
		return (g_status = 126, redire_err(cmd, ": Permission denied"), NULL);
	if (is_slash(cmd) && access(cmd, F_OK | X_OK) == 0)
		return (g_status = 126, ft_strdup(cmd));
	return (search_path(cmd, env));
}

char	**double_env(t_env *env)
{
	char	**ret;
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	ret = malloc((ft_sizeenv(env) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (env)
	{
		tmp1 = ft_strdup("=");
		tmp2 = ft_strdup(env->value_env);
		ret[i] = ft_strjoin(ft_strdup(env->name_env), tmp1);
		ret[i] = ft_strjoin(ret[i], tmp2);
		free_null(&tmp1);
		free_null(&tmp2);
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
		doubfree(tenv);
		free_null(&path);
	}
	return (doubfree(tenv), tenv = NULL, 0);
}
