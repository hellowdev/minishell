/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:07 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/02 11:34:19 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	outfile_append(char *s, t_token **head)
{
	int i;
	i = 0;
	if (s[i] == '>' && s[i + 1] != '>')
		i += red_outfile(head);
	else if (s[i] == '>' && s[i + 1] == '>')
		i += append(head);
	return (i);
}

int	red_outfile(t_token **token)
{
    t_token *new;
	new = ft_lstnew(ft_strdup(">"), RED_OUT);
	ft_lstadd_back(token, new);
	return (1);
}

int	append(t_token **token)
{
	t_token *new;
	new = ft_lstnew(ft_strdup(">>"), APPEND);
	ft_lstadd_back(token, new);
	return (2);
}