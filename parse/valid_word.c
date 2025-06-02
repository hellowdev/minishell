/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:50:27 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/02 23:45:19 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_spcharc(char c)
{
	if (c == '&')
		return (update_status("&"), 1);
	else if (c == '(')
		return (update_status("("), 1);
	else if (c == ')')
		return (update_status(")"), 1);
	else if (c == '#')
		return (update_status("#"), 1);
	else if (c == ';')
		return (update_status(";"), 1);
	return (0);
}

int	double_qt(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != 34)
		i++;
	return (i);
}

int	single_qt(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != 39)
		i++;
	return (i);
}
