/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:50:27 by ychedmi           #+#    #+#             */
/*   Updated: 2025/04/23 18:28:11 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_spcharc(char c)
{
	if (c == '&' || c == '(' || c == ')'\
	|| c == '#' || c == ';')
		return (1);
	return (0);
}

int	valid_word(t_token *head)
{
	int i;
	i = 0;
	if (head->type != WORD)
		return (0);
	while (head->value[i])
	{
		// printf(">> word\n");
		if (head->value[i] == 34)
			i += doub_qt(&head->value[i]);
		else if (head->value[i] == 39)
			i += sing_qt(&head->value[i]);
		if (is_spcharc(head->value[i]) != 0)
			return (0);
		i++;
	}
    return (1);
}
