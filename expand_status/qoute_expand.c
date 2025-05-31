/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:25 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/30 15:25:06 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	doub_qt(char *s, char **str, bool *checker)
{
	int	i;

	i = 0;
	if (s[i] == 34)
	{
		i = 1;
		if (s[i] == 34 && s[i + 1] != '\0')
			return (2);
		else if (s[i] == 34 && s[i + 1] == '\0')
			return (*str = ft_strjoin(*str, ft_strdup("")), 2);
		if (*checker == true)
			*checker = false;
		else
			*checker = true;
		return (1);
	}
	return (i);
}

int	sing_qt(char *s, char **str)
{
	int	i;

	i = 0;
	if (s[i] == 39)
	{
		i = 1;
		if (s[i] == 39 && s[i + 1] != '\0')
			return (2);
		else if (s[i] == 39 && s[i + 1] == '\0')
			return (*str = ft_strjoin(*str, ft_strdup("")), 2);
		while (s[i] && s[i] != 39)
			i++;
		if (i > 1)
		{
			*str = ft_strjoin(*str, ft_substr(s, 1, i - 1));
			return (i + 1);
		}
	}
	return (i);
}
