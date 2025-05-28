/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:56:07 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/28 21:34:40 by ychedmi          ###   ########.fr       */
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

int	built_in(t_parce *data, t_env **env, int *status)
{
	int tmp;

	if (!data->cmd)
		return (0);
	tmp = dup(1);
	if (match_cmd(data->cmd[0], "env")) // "cmd" only not path of cmd mean is a builtin cmd
		return (dup_outfile(data->outfiles, data->append),
		env_cmd(*env), dup2(tmp, 1), close(tmp), 1);
		
	if (match_cmd(data->cmd[0], "cd"))
		return (cd_cmd(data->cmd, env, status), 1);
		
	if (match_cmd(data->cmd[0], "echo"))
		return (dup_outfile(data->outfiles, data->append), 
		echo_cmd(data->cmd), dup2(tmp, 1), close(tmp), 1);
		
	if (ft_strcmp(data->cmd[0], "export") == 0)
		return (dup_outfile(data->outfiles, data->append),
		export_cmd(data->cmd, env), dup2(tmp, 1), close(tmp), 1);
		
	if (ft_strcmp(data->cmd[0], "unset") == 0)
		return (unset_cmd(data->cmd, env), 1);
	if (match_cmd(data->cmd[0], "pwd"))
		return (dup_outfile(data->outfiles, data->append),
		pwd_cmd(data->cmd), dup2(tmp, 1), close(tmp), 1);
		
	return (close(tmp), 0);
}
