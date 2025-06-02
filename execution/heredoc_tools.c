/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:36:22 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 00:55:17 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strlen_herdoc(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

int	ft_strcm_doc(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i] && s1[i] != '\n')
		i++;
	if (s1[i] == '\n')
	{
		i++;
		return (s1[i] - s2[i - 1]);
	}
	return (s1[i] - s2[i]);
}

int	redire_err(char *file, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(err, 2);
	if (err)
		write(2, "\n", 1);
	return (-1);
}
