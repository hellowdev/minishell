/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:26:11 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/11 15:26:24 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	words(char const *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] != c && ((s[i + 1]) == '\0' || s[i + 1] == c))
			counter++;
		i++;
	}
	return (counter);
}

static void	*freez(char **p, int m)
{
	int	i;

	i = 0;
	while (i < m)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

static char	**copy(char const *s, char c, char **p)
{
	int	i;
	int	f;
	int	len;
	int	word;

	word = words(s, c);
	f = 0;
	i = 0;
	while (f < word)
	{
		len = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i + len] && s[i + len] != c)
			len++;
		p[f] = ft_calloc((len + 1), sizeof(char));
		if (!p[f])
			return (freez(p, f));
		ft_memcpy(p[f], &s[i], len);
		f++;
		i += len;
	}
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		cnt;

	if (!s)
		return (NULL);
	cnt = words(s, c);
	p = ft_calloc((cnt + 1), sizeof(char *));
	if (!p)
		return (NULL);
	p = copy(s, c, p);
	return (p);
}