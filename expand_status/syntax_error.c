/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:16:06 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 18:30:32 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_word(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34)
			i += double_qt(&s[i]);
		else if (s[i] == 39)
			i += single_qt(&s[i]);
		if (is_spcharc(s[i]) != 0)
			return (-1);
		i++;
	}
	return (1);
}

int	calc_qout(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			i += double_qt(&s[i]);
			if (!s[i])
				return (update_status("\""), -1);
		}
		else if (s[i] == 39)
		{
			i += single_qt(&s[i]);
			if (!s[i])
				return (update_status("'"), -1);
		}
		i++;
	}
	return (1);
}

void	update_status(char *s)
{
	write(2, "minishell: syntax error near unexpected token `", 48);
	write(2, s, ft_strlen(s));
	write(2, "'\n", 2);
	g_status = 258;
}
