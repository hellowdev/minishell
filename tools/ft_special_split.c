/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:32:53 by ychedmi           #+#    #+#             */
/*   Updated: 2025/07/02 20:04:56 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] && s[i] == 34)
			i += double_qt(&s[i]);
		else if (s[i] && s[i] == 39)
			i += single_qt(&s[i]);
		if (s[i] && s[i] != c && ((s[i + 1]) == '\0' || s[i + 1] == c))
			counter++;
		if (!s[i])
			break ;
		i++;
	}
	return (counter);
}

static void	*frfr(char **p, int m)
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

int	len_qoutes(char *s)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	if (s[i + len] == 34)
		len += double_qt(&s[i + len]);
	else if (s[i + len] == 39)
		len += single_qt(&s[i + len]);
	return (len);
}

static char	**copy_str(char *s, char sep, char **p)
{
	int	i;
	int	f;
	int	len;
	int	word;

	word = count_words(s, sep);
	f = 0;
	i = 0;
	while (f < word)
	{
		len = 0;
		while (s[i] && s[i] == sep)
			i++;
		while (s[i + len] && s[i + len] != sep)
			len += len_qoutes(&s[i + len]) + 1;
		p[f] = ft_calloc((len + 1), sizeof(char));
		if (!p[f])
			return (frfr(p, f));
		ft_memcpy_qoute(p[f], &s[i], len);
		f++;
		i += len;
	}
	return (p);
}

char	**ft_salma_split(char *s, char c)
{
	char	**p;
	int		cnt;

	if (!s)
		return (NULL);
	cnt = count_words(s, c);
	p = ft_calloc((cnt + 1), sizeof(char *));
	if (!p)
		return (NULL);
	p = copy_str(s, c, p);
	return (p);
}
