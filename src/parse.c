/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:10 by ychedmi           #+#    #+#             */
/*   Updated: 2025/04/18 12:52:41 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenization(char *s, t_token **head)
{
	int i;
	int j;

	j = 0;
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

int	pars_ing(t_token *head)
{
	
	t_parce *newnode = malloc(sizeof(t_parce));
    
    if (!newnode)
        return (NULL);
	
	if (head->type == PIPE)
		return (ft_lstclear(head), write(2, "syntax error near unexpected token", 35), 258);	
	while (head)
	{
		infile_data(head, newnode);
		outfile_data(head, newnode);
		append_data(head, newnode);
		heredoc_data(head, newnode);
		cmd_data(head, newnode);
		head = head->next;
	}
	
}

void	main_parse(char *s)
{
	t_token *head;

	head = NULL;
	tokenization(s, &head);
	pars_ing(head);
	
    // syntax_validation(head);
}