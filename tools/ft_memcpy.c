/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:36:38 by ychedmi           #+#    #+#             */
/*   Updated: 2025/07/02 20:01:11 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned int	i;

	i = 0;
	if (dest == src)
		return (dest);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

int	qoutes_check(bool *checker)
{
	if (*checker == true)
		*checker = false;
	else
		*checker = true;
	return (1);
}

void	*ft_memcpy_qoute(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned int	i;
	int				j;
	bool			check_db;
	bool			check_sg;

	check_db = false;
	check_sg = false;
	i = 0;
	j = 0;
	if (dest == src)
		return (dest);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < n)
	{
		if (s[i] == 34 && !check_sg)
			i += qoutes_check(&check_db);
		if (s[i] == 39 && !check_db)
			i += qoutes_check(&check_sg);
		d[j++] = s[i++];
	}
	return (dest);
}
