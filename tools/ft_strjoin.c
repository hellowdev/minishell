/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:41:33 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/04 16:40:56 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
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
		return (s1);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!p)
		return (free(s1), NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[t])
		p[i++] = s2[t++];
	p[i] = '\0';
	free(s1);
	return (p);
}
