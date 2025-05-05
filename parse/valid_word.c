/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:50:27 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/04 17:10:18 by ychedmi          ###   ########.fr       */
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

int	double_qt(char *s)
{
	int i;

	i = 1;
	while (s[i] && s[i] != 34)
		i++;
	return (i);
}

int	single_qt(char *s)
{
	int i;

	i = 1;
	while (s[i] && s[i] != 39)
		i++;
	return (i);
}

int	valid_word(t_token *head)
{
	int i;
	i = 0;
	t_token *tmp;
	tmp = head;
	if (head->type != WORD)
		return (0);
	while (head->value[i])
	{
		if (head->value[i] == 34)
			i += double_qt(&head->value[i]);
		else if (head->value[i] == 39)
			i += single_qt(&head->value[i]);
		if (is_spcharc(head->value[i]) != 0)
			return (0);
		i++;
	}
    return (1);
}
//	all variable in env
// 	[$HOME] ---> name: HOME | value: user/..
// output = 