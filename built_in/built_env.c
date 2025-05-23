/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:56:07 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/23 21:43:11 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	match_cmd(char *user_cmd, char *matcha)
{
	int i;
	int j;
	
	j = 0;
	i = 0;
	while (user_cmd[i])
	{
		if (user_cmd[i] != matcha[i] && user_cmd[i] != matcha[i] - 32)
			return (0);
		i++;
		j++;	
	}	
	return (1);
}

void	env_cmd(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name_env, env->value_env);
		env = env->next;
	}
}

int	built_in(char **cmd, t_env **env, int *status)
{
	(void)status;
	if (!cmd)
		return (-1);
	
	if (match_cmd(cmd[0], "env")) // "cmd" only not path of cmd mean is a builtin cmd
		return (env_cmd(*env), 1);
	if (match_cmd(cmd[0], "cd"))
		return (cd_cmd(cmd, env, status), 1);
	if (match_cmd(cmd[0], "echo"))
		return (echo_cmd(cmd), 1);
	if (ft_strcmp(cmd[0], "export") == 0)
		return (export_cmd(cmd, env), 1);
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (unset_cmd(cmd, env), 1);
	if (match_cmd(cmd[0], "pwd"))
		return (pwd_cmd(cmd), 1);
	return (0);
}
