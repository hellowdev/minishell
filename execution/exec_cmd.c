/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:58:34 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/24 12:31:13 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (0);
}
