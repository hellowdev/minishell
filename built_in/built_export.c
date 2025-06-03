/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:08:22 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 21:37:14 by ychedmi          ###   ########.fr       */
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
		{
			if (!env->value_env)
				printf("declare -x %s\n", env->name_env);
			else
				printf("declare -x %s=\"%s\"\n", env->name_env, env->value_env);
		}
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
	char	*name;
	char	*value;

	tmp = *env;
	name = ft_substr(var, 0, len_equal(var));
	value = ft_substr(var, len_equal(var) + 1, ft_strlen(var));
	if (!*value)
		free_null(&value);
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
	int	i;

	i = 0;
	if (s[i] == '=')
		return (1);
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
	int	i;

	if (cmd[0] && !cmd[1])
		display_export(*env);
	i = 1;
	g_status = 0;
	while (cmd[i])
	{
		if (valid_idf_exp(cmd[i]) == 1 || !*cmd[i])
		{
			write(2, "minishell: export: `", 20);
			write(2, cmd[i], ft_strlen(cmd[i]));
			write(2, "': not a valid identifier\n", 26);
			g_status = 1;
		}
		else
			add_env(env, cmd[i]);
		i++;
	}
}
