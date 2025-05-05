/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:25 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/05 10:48:29 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	doub_qt(char *s, char **str)
{
	int i;
	i = 0;
	if (s[i] == 34)
	{
		i = 1;
		if (s[i] == 34 && !ft_isspace(s[i + 1]) && s[i + 1])
			return (2);
		else if (s[i] == 34 && (ft_isspace(s[i + 1]) || !s[i + 1]))
			return (*str = ft_strdup(""), 2);
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

int	sing_qt(char *s, char **str)
{
	int i;

	i = 0;
	if (s[i] == 39)
	{
		i = 1;
		if (s[i] == 39)
			return (2);
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

int	check_chac(char *s, char **str)
{
	int i;

	i = 0;
	while (s[i] && s[i] != 34 && s[i] != 39 && !spec_char(s[i]))
		i++;
	if (i)
	{
		*str = ft_substr(s, 0, i);
		return (i);
	}
	free_null(str);
	return (i);
}
