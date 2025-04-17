/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:10 by ychedmi           #+#    #+#             */
/*   Updated: 2025/04/17 18:28:49 by ychedmi          ###   ########.fr       */
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
	int		i;
	int		c;
	int		o;
	t_parce	*list;

	i = 0;
	c = 0;
	o = 0;
	if (head->type == PIPE)
		return (free(head), write(2, "syntax error near unexpected token `|'", 39), 1);
	else if (head->type == WORD)
		list->cmd[c++] = ft_strdup(head->value);
	while (head)
	{
		if (head->type == REDIRECT_IN && valid_word(head->next) == 1)
		{
			list->infiles[i++] = ft_strdup(head->next->value);
			head = head->next;
		}
		else if (head->type == REDIRECT_OUT && valid_word(head->next))
		{
			list->outfiles[o++] = ft_strdup(head->next->value);
			head = head->next;
		}
		
		head = head->next;
	}
	
}

void	main_parse(char *s)
{
	t_token *head;

	head = NULL;
	tokenization(s, &head);
	pars_ing(&head);
	
    // syntax_validation(head);
}