/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doubjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:18:22 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/04 13:12:20 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_doubjoin(char **tab1, char **tab2)
{
	char	**p;
	int		i;
	int		v;

	p = malloc((double_len(tab1) + double_len(tab2) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	i = 0;
	while (tab1[i])
	{
		p[i] = ft_strdup(tab1[i]);
		i++;
	}
	v = 0;
	while (tab2[v])
		p[i++] = ft_strdup(tab2[v++]);
	p[i] = NULL;
	doubfree(tab1);
	return (p);
}

char	**ft_special_join(char **tab1, char **tab2)
{
	char	**p;
	int		i;
	int		v;
	int		len2;

	len2 = double_len(tab2) + 1;
	p = malloc((double_len(tab1) + len2 + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	i = 0;
	while (tab1[i])
	{
		p[i] = ft_strdup(tab1[i]);
		i++;
	}
	v = 0;
	while (v < len2)
		p[i++] = ft_strdup(tab2[v++]);
	p[i] = NULL;
	doubfree(tab1);
	return (p);
}

