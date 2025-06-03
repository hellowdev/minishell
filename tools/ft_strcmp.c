/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:07:46 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 13:27:19 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*skip_sp(char *s)
{
	int		i;
	int		v;
	char	*p;

	i = 0;
	while (s[i] == 32)
		i++;
	v = ft_strlen(s) - 1;
	while (s[v] && s[v] == 32)
		v--;
	p = ft_substr(s, i, v + 1);
	return (p);
}
