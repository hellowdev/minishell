/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:56:07 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/02 23:37:33 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	match_cmd(char *user_cmd, char *matcha)
{
	int i;

	i = 0;
	while (matcha[i])
	{
		if (user_cmd[i] != matcha[i] && user_cmd[i] != matcha[i] - 32)
			return (0);
		i++;
	}	
	return (1);
}

void	env_cmd(t_env *env)
{
	while (env)
	{
		if (env->name_env && env->value_env)
			printf("%s=%s\n", env->name_env, env->value_env);
		env = env->next;
	}
}

int	half_builtin(t_parce *data, t_env **env, int tmp)
{	
	if (data->cmd[0] && match_cmd(data->cmd[0], "echo"))
	{
		if (dup_outfile(data->outfiles, data->append) == -1)
			return (1);
		return (echo_cmd(data->cmd), dup2(tmp, 1), close(tmp), 1);
	}
	if (data->cmd[0] && ft_strcmp(data->cmd[0], "export") == 0)
	{
		if (dup_outfile(data->outfiles, data->append) == -1) 
			return (1); 
		return (export_cmd(data->cmd, env), dup2(tmp, 1), close(tmp), 1);
	}
	if (data->cmd[0] && ft_strcmp(data->cmd[0], "unset") == 0)
		return (unset_cmd(data->cmd, env), 1);
	if (data->cmd[0] && match_cmd(data->cmd[0], "pwd"))
	{
		if (dup_outfile(data->outfiles, data->append) == -1)
			return (1);
		return (pwd_cmd(data->cmd), dup2(tmp, 1), close(tmp), 1);
	}
	return (0);
}

int	built_in(t_parce *data, t_env **env)
{
	int tmp;

	if (!data->cmd)
		return (0);
	tmp = dup(1);
	if (data->cmd[0] && match_cmd(data->cmd[0], "env"))
	{
		if (dup_outfile(data->outfiles, data->append) == -1)
			return (close(tmp), 1);
		return (env_cmd(*env), dup2(tmp, 1), close(tmp), 1);
	}
	if (data->cmd[0] && match_cmd(data->cmd[0], "cd"))
		return (cd_cmd(data->cmd, env), 1);
	if (data->cmd[0] && ft_strcmp(data->cmd[0], "exit") == 0)
		return (exit_cmd(data, data->cmd, *env), 1);
	if (half_builtin(data, env, tmp) == 1)
		return (close(tmp), 1);
	return (close(tmp), 0);
}
