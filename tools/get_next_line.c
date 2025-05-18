/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:41:34 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/17 11:05:59 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*afternwl(char *str)
{
	int		i;
	int		j;
	char	*p;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			p = malloc(ft_strlen(str) - i + 1);
			if (!p)
				return (free(str), NULL);
			while (str[i])
				p[j++] = str[(i++) + 1];
			p[j] = '\0';
			free(str);
			return (p);
		}
		i++;
	}
	free(str);
	return (NULL);
}

char	*takeme(char *str)
{
	char	*dog;
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (new_line(str) != -1)
		i = new_line(str);
	else
		i = ft_strlen(str);
	dog = malloc(i + 1);
	if (!str || !dog)
		return (NULL);
	while (str[j] && j < i)
	{
		dog[j] = str[j];
		j++;
	}
	dog[j] = '\0';
	return (dog);
}

char	*get_next_line(int fd)
{
	int			v;
	char		*buffer;
	static char	*str;
	char		*all;

	if (!str)
		str = takeme("");
	v = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	while (v > 0 && new_line(str) == -1)
	{
		v = read(fd, buffer, BUFFER_SIZE);
		if (v < 0 || !buffer)
			return (free(str), free(buffer), str = NULL, NULL);
		buffer[v] = '\0';
		str = join(str, buffer);
	}
	free(buffer);
	if (!str || (v == 0 && str[0] == '\0'))
		return (free(str), str = NULL, NULL);
	all = takeme(str);
	if (!all)
		return (free(str), str = NULL, NULL);
	str = afternwl(str);
	return (all);
}
