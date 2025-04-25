/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:10 by ychedmi           #+#    #+#             */
/*   Updated: 2025/04/25 12:24:51 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parce	*data_alloc(t_token *head, t_env *env)
{
	t_parce *newnode;
		
	newnode = malloc(sizeof(t_parce)); // alloc  all node
	if (!newnode)
        return NULL;
	newnode->next = NULL;
	if (count_cmd(head, newnode, env) == 1)
		return (free_doublst(newnode), NULL);
	if (count_outfiles(head, newnode, env) == 1)
		return (free_doublst(newnode), NULL);
	if (count_infiles(head, newnode, env) == 1)
		return (free_doublst(newnode), NULL);
	if (count_heredoc(head, newnode, env) == 1)
		return (free_doublst(newnode), NULL);
	return (newnode);
}

void	after_pipe(t_token **head, t_token **tmp, t_env *env, t_parce **lst)
{
	t_parce *newnode;

	while ((*head))
	{
		if ((*head)->type == PIPE && (*head)->next)
		{
			(*head) = (*head)->next;
			newnode = data_alloc((*head), env);
			if (!newnode)
				return (ft_lstclear(*tmp),free_doublst(*lst));
			parse_add_back(lst, newnode);
		}
		else if ((*head)->type == PIPE && !(*head)->next)
			return ((ft_lstclear((*head)),free_doublst(*lst)), update_status(env));
		(*head) = (*head)->next;
	}
}

void	pars_ing(t_parce **lst, t_env *env, t_token *head)
{
	t_parce *newnode;
	t_token *tmp;

	tmp = head;
	if (head->type == PIPE)
		return (update_status(env));
	newnode = data_alloc(head, env);
	if (!newnode)
		return (ft_lstclear(head));
	parse_add_back(lst, newnode);
	after_pipe(&head, &tmp, env, lst);
}
