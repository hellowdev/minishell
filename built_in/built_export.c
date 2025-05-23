/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:08:22 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/23 13:01:23 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_export(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (ft_strcmp(env->name_env, "_") != 0)
			printf("declare -x %s=\"%s\"\n", env->name_env, env->value_env);
		if (ft_strcmp(env->name_env, "OLDPWD") == 0)
			i = 1;
		env = env->next;
	}
	if (i == 0)
		printf("declare -x OLDPWD\n");
}

void	add_env(t_env **env, char *var)
{
	t_env	*new;
	t_env	*tmp;
	char 	*name;
	char	*value;

	tmp = *env;
	name = ft_substr(var, 0, len_equal(var));
	value = ft_substr(var, len_equal(var) + 1, ft_strlen(var));
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name_env) == 0)
		{
			free(tmp->value_env);
			tmp->value_env = value;
			return ;
		}
		tmp = tmp->next;
	}
	new = lstnew_env(name, value);
	env_add_back(env, new);
}

int	valid_idf_exp(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalpha(s[i]) && s[i] != '_' && (i == 0 || !ft_isdigit(s[i])))
			return (1);
		i++;
	}
	return (0);
}

void	export_cmd(char **cmd, t_env **env)
{
	int i;
	
	if (cmd[0] && !cmd[1])
		display_export(*env);
	i = 1;
	while (cmd[i])
	{
		if (valid_idf_exp(cmd[i]) == 1)
			redire_err(cmd[i], ": not a valid identifier");
		add_env(env, cmd[i]);
		i++;
	}
}
