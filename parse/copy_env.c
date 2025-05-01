/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:49:58 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/01 11:12:31 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_equal(char *s)
{
	int cnt;

	cnt = 0;
	while (s[cnt] && s[cnt] != '=')
		cnt++;
	return (cnt);
}

void	copy_env(t_env **head)
{
	int		i;
	t_env	*new;
	char	*name;
	char	*value;
	
	i = 0;
	while (environ[i])
	{
		name = ft_substr(environ[i], 0, len_equal(environ[i]));
		value = ft_substr(environ[i], len_equal(environ[i]) + 1, ft_strlen(environ[i]));
		new = lstnew_env(name, value);
		env_add_back(head, new);
		i++;
	}
	new = lstnew_env(ft_strdup("status"), ft_strdup("0"));
	env_add_back(head, new);
}
