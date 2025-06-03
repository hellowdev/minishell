/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slash_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:32:42 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 18:18:46 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_slash_join(char const *s1, char const *s2)
{
	size_t	i;
	size_t	t;
	char	*p;

	i = 0;
	t = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i++] = '/';
	while (s2[t])
		p[i++] = s2[t++];
	p[i] = '\0';
	return (p);
}
