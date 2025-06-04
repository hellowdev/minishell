/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:25 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/04 16:53:32 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	doub_qt(char *s, char **str, bool *inside_dq)
{
	int		i;
	char	*tmp;

	i = 0;
	if (s[i] == 34)
	{
		i = 1;
		if (s[i] == 34 && s[i + 1] != '\0')
			return (2);
		else if (s[i] == 34 && s[i + 1] == '\0')
		{
			tmp = ft_strdup("");
			return (*str = ft_strjoin(*str, tmp), free_null(&tmp), 2);
		}
		if (*inside_dq == true)
			*inside_dq = false;
		else
			*inside_dq = true;
		return (1);
	}
	return (i);
}

int	sing_qt(char *s, char **str)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	if (s[i] == 39)
	{
		i = 1;
		if (s[i] == 39 && s[i + 1] != '\0')
			return (2);
		else if (s[i] == 39 && s[i + 1] == '\0')
			return (tmp1 = ft_strdup(""), *str = \
			ft_strjoin(*str, tmp1), free_null(&tmp1), 2);
		while (s[i] && s[i] != 39)
			i++;
		if (i > 1)
		{
			tmp2 = ft_substr(s, 1, i - 1);
			*str = ft_strjoin(*str, tmp2);
			return (free_null(&tmp2), i + 1);
		}
	}
	return (i);
}
