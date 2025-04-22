/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfartah <sfartah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:10 by ychedmi           #+#    #+#             */
/*   Updated: 2025/04/18 15:30:13 by sfartah          ###   ########.fr       */
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

void	data_alloc(t_token *head, t_parce **newnode)
{
	int c;
	int i;
	int o;
	int h;

	c = count_cmd(head);
	i = count_infiles(head);
	o = count_outfiles(head);
	h = count_heredoc(head);
	if (c != 0)
		(*newnode)->cmd = malloc((c + 1) * sizeof(char *));
	if (h != 0)
		(*newnode)->heredoc = malloc((h + 1) * sizeof(char *));
	if (i != 0)
		(*newnode)->infiles = malloc((i + 1) * sizeof(char *));
	if (o != 0)
	{
		(*newnode)->outfiles = malloc((o + 1) * sizeof(char *));
		(*newnode)->append = malloc(o * sizeof(bool));
	}
}

int	pars_ing(t_env *env, t_token *head)
{
	t_parce	*lst;
	t_parce *newnode;

	newnode = malloc(sizeof(t_parce));
	if (!newnode)
        return (NULL);
	data_alloc(head, &newnode);

	if (head->type == PIPE)
		return (ft_lstclear(head), write(2, "syntax error near unexpected token", 35), 258);	
	while (head)
	{
		infile_data(env, head, newnode);
		outfile_data(env, head, newnode);
		heredoc_data(env, head, newnode);
		cmd_data(env, head, newnode);
		head = head->next;
	}
	ft_lstadd_back(&lst, newnode);
}

void	main_parse(t_env *env, char *s)
{
	t_token *head;

	head = NULL;
	tokenization(s, &head);
	pars_ing(env, head);
	
    // syntax_validation(head);
}