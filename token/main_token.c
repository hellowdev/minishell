/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:14:17 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/30 09:27:57 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenization(char *s, t_token **head)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i += infile_heredoc(&s[i], head);
		i += outfile_append(&s[i], head);
		i += handle_pipe(&s[i], head);
		i += check_words(&s[i], head);
		if (ft_isspace(s[i]) == 1)
			i++;
	}
}

int	handle_pipe(char *s, t_token **head)
{
	t_token	*new;

	if (s[0] == '|')
	{
		new = ft_lstnew(ft_strdup("|"), PIPE);
		ft_lstadd_back(head, new);
		return (1);
	}
	return (0);
}
