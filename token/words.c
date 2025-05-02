/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:25 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/02 12:46:02 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	doub_qt(char *s, t_word *data)
{
	int i;
	i = 0;
	if (s[i] == 34)
	{
		i = 1;
		while (s[i] && s[i] != 34)
			i++;
		if (i > 1)
		{
			data->strdb = ft_substr(s, 1, i - 1);
			return (i + 1);
		}
	}
	data->strdb = NULL;
	return (i);
}

int	sing_qt(char *s, t_word *data)
{
	int i;

	i = 0;
	if (s[i] == 39)
	{
		i = 1;
		while (s[i] && s[i] != 39)
			i++;
		if (i > 1)
		{
			data->strsg = ft_substr(s, 1, i - 1);
			return (i + 1);
		}
	}
	data->strsg = NULL;
	return (i);
}

int	check_chac(char *s, t_word *data)
{
	int i;

	i = 0;
	while (s[i] && s[i] != 34 && s[i] != 39 && !spec_char(s[i]))
		i++;
	if (i)
	{
		data->str = ft_substr(s, 0, i);
		return (i);
	}
	free(data->str);
	data->str = NULL;
	return (i);
}
