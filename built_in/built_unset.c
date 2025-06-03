/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:25:12 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 10:14:12 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_idf(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isalpha(s[i]) && s[i] != '_' && (i == 0 || !ft_isdigit(s[i])))
			return (1);
		i++;
	}
	return (0);
}

void	env_delete(t_env **env, char *name)
{
	t_env *tmp;
	t_env *deltmp;

	tmp = (*env);
	deltmp = (*env);
	if (ft_strcmp(tmp->name_env, name) == 0)
	{
		(*env) = (*env)->next;
		return (free(deltmp->value_env), free(deltmp->name_env), free(deltmp));
	}
	while (tmp)
	{
		if (tmp->next && ft_strcmp(tmp->next->name_env, name) == 0)
		{
			deltmp = tmp->next;
			tmp->next = deltmp->next;
			return (free(deltmp->value_env), free(deltmp->name_env), free(deltmp));
		}
		tmp = tmp->next;
	}
}

void	unset_cmd(char **cmd, t_env **env)
{
	int i;

	i = 1;
	status = 0;
	while (cmd[i])
	{
		if (valid_idf(cmd[i]) == 1 || !*cmd[i])
		{
			write(2, "minishell: unset: `", 20);
			write(2, cmd[i], ft_strlen(cmd[i]));
			write(2, "': not a valid identifier\n", 26);
			status = 1;
		}
		else
			env_delete(env, cmd[i]);
		i++;
	}
}