/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:58:34 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/29 20:57:20 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(t_env *env)
{
	char	**mypath;
	char	*path;

	mypath = NULL;
	path = env_searsh(env, "PATH");
	mypath = ft_split(path, ':');
	return (free_null(&path), mypath);
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
	char	*apatapati;
	char	**tenv;
	int		i;

	tenv = double_env(testenv);
	i = 0;
	if (data->cmd && *data->cmd)
	{
		apatapati = path(testenv, data->cmd[i]);
		if (!apatapati)
			return (doubfree(tenv), -1);
		execve(apatapati, data->cmd, tenv);
		doubfree(tenv);
		free_null(&apatapati);
	}
	return (doubfree(tenv), tenv = NULL, 0);
}
