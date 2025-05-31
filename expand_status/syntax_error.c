/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:16:06 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/30 12:24:45 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_word(char *s, int *status)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34)
			i += double_qt(&s[i]);
		else if (s[i] == 39)
			i += single_qt(&s[i]);
		if (is_spcharc(status, s[i]) != 0)
			return (-1);
		i++;
	}
	return (1);
}

int	calc_qout(char *s, int *status)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			i += double_qt(&s[i]);
			if (!s[i])
				return (update_status(status, "\""), -1);
		}
		else if (s[i] == 39)
		{
			i += single_qt(&s[i]);
			if (!s[i])
				return (update_status(status, "'"), -1);
		}
		i++;
	}
	return (1);
}

void	update_status(int *status, char *s)
{
	write(2, "minishell: syntax error near unexpected token `", 48);
	write(2, s, ft_strlen(s));
	write(2, "'\n", 2);
	*status = 258;
}
