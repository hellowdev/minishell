/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deljoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:10:01 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/30 15:11:06 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dblqt(char *s, char **str, bool *check)
{
	int	i;

	i = 0;
	if (s[i] == 34)
	{
		*check = true;
		i = 1;
		if (s[i] == 34 && s[i + 1])
			return (ft_strdup(""), 2);
		while (s[i] && s[i] != 34)
			i++;
		if (i > 1)
		{
			*str = ft_substr(s, 1, i - 1);
			return (i + 1);
		}
	}
	free_null(str);
	return (i);
}

int	check_sgqt(char *s, char **str, bool *check)
{
	int	i;

	i = 0;
	if (s[i] == 39)
	{
		*check = true;
		i = 1;
		if (s[i] == 39)
			return (ft_strdup(""), 2);
		while (s[i] && s[i] != 39)
			i++;
		if (i > 1)
		{
			*str = ft_substr(s, 1, i - 1);
			return (i + 1);
		}
	}
	free_null(str);
	return (i);
}

int	check_char(char *s, char **str)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != 34 && s[i] != 39)
		i++;
	if (i)
	{
		*str = ft_substr(s, 0, i);
		return (i);
	}
	free_null(str);
	return (i);
}

char	*deljoin(char *s, bool *check_quote)
{
	int		i;
	char	*p;
	char	*str;

	str = NULL;
	p = NULL;
	*check_quote = false;
	i = 0;
	while (s[i])
	{
		i += check_char(&s[i], &str);
		p = ft_strjoin(p, str);
		free_null(&str);
		i += check_dblqt(&s[i], &str, check_quote);
		p = ft_strjoin(p, str);
		free_null(&str);
		i += check_sgqt(&s[i], &str, check_quote);
		p = ft_strjoin(p, str);
		free_null(&str);
	}
	return (p);
}
