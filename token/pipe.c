/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:14 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/02 11:34:29 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_space(char *s)
{
	int i;
	i = 0;
	while (s[i] && ft_isspace(s[i]) == 1)
		i++;
	return (i - 1);
}

int	handle_pipe(char *s, t_token **head)
{
	
	t_token *new;
	if (s[0] == '|')
	{	
		new = ft_lstnew(ft_strdup("|"), PIPE);
		ft_lstadd_back(head, new);
		return (1);
	}
	return (0);
}
