/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:43:31 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 18:19:03 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join(char *str1, char *str2)
{
	int		i;
	char	*p;
	int		n;

	n = 0;
	i = 0;
	if (!str1)
		return (takeme(str2));
	if (!str2)
		return (takeme(str1));
	p = malloc(ft_strlen(str2) + ft_strlen(str1) + 1);
	if (!p)
		return (free(str1), NULL);
	while (str1[i])
	{
		p[i] = str1[i];
		i++;
	}
	while (str2[n])
		p[i++] = str2[n++];
	p[i] = '\0';
	free(str1);
	return (p);
}

int	new_line(char *buff)
{
	int	i;

	i = 0;
	if (!buff)
		return (0);
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-1);
}
