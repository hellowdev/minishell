/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:59:22 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/04 16:56:35 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_space(char *str)
{
	int	i;
	int	j;
	int	chr;

	chr = 0;
	j = 0;
	if (!str || !*str)
		return (0);
	i = ft_strlen(str);
	while (str[j])
	{
		if (str[j] != 32 && str[j] != '\0')
			chr = 1;
		j++;
	}
	if (str[i - 1] == 32 && chr == 1)
		return (1);
	return (0);
}

int	strlen_dol(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' || s[i] == 34 || s[i] == 39)
			return (i);
		i++;
	}
	return (i);
}

int	special_char(char c)
{
	if (!ft_isalpha(c) && !ft_isdigit(c) && c != '_')
		return (1);
	return (0);
}

int	check_dol_sp(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == '$' || special_char(s[i]) == 1)
			return (i);
		i++;
	}
	return (i);
}

char	*env_searsh(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name_env, name) == 0)
			return (ft_strdup(env->value_env));
		env = env->next;
	}
	return (NULL);
}
