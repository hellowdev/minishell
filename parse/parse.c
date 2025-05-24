/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:10 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/24 11:17:21 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_input(t_token *list)
{
	bool	checker;

	while (list && list->type != PIPE)
	{
		if (list->type == HEREDOC)
			checker = true;
		else if (list->type == RED_IN)
			checker = false;
		list = list->next;
	}
	return (checker);	
}

t_parce	*data_alloc(t_token *head, int *status, t_env *env)
{
	t_parce *newnode;

	newnode = malloc(sizeof(t_parce));
	if (!newnode)
        return NULL;
	newnode->input = check_input(head);
	newnode->next = NULL;
	newnode->cmd = NULL;
	newnode->infiles = NULL;
	newnode->outfiles = NULL;
	newnode->heredoc = NULL;
	newnode->append = NULL;
	count_cmd(head, newnode, status, env);
	if (count_outfiles(head, newnode, status, env) == 1)
		return (free_doublst(&newnode), NULL);
	if (count_infiles(head, newnode, status, env) == 1)
		return (free_doublst(&newnode), NULL);
	if (count_heredoc(head, newnode, status) == 1)
		return (free_doublst(&newnode), NULL);
	return (newnode);
}

void	after_pipe(t_token *head, int *status, t_parce **lst, t_env *env)
{
	t_parce *newnode;

	while (head)
	{
		if (head->type == PIPE && head->next && head->next->type != PIPE)
		{
			head = head->next;
			if (head->type == PIPE)
				return (free_doublst(lst), update_status(status, "|"));
			newnode = data_alloc(head, status, env);
			if (!newnode)
				return (free_doublst(lst));
			parse_add_back(lst, newnode);
		}
		else if (head->type == PIPE && !head->next)
			return (free_doublst(lst), update_status(status, "|"));
		head = head->next;
	}
}


void	pars_ing(t_parce **lst, int *status, t_token *head, t_env *env)
{
	t_parce *newnode;
	t_token *tmp;

	tmp = head;
	if (head->type == PIPE)
		return (update_status(status, "|"));
	newnode = data_alloc(head, status, env);
	if (!newnode)
	{
		*lst = NULL;// for not execute in this list
		return ;
	}
	parse_add_back(lst, newnode);
	after_pipe(head, status, lst, env);
}
