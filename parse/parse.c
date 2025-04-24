/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:10 by ychedmi           #+#    #+#             */
/*   Updated: 2025/04/24 13:09:28 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parce	*data_alloc(t_token *head)
{
	t_parce *newnode;
	
	
	newnode = malloc(sizeof(t_parce)); // alloc  all node
	if (!newnode)
        return NULL;
	newnode->next = NULL;
	count_cmd(head, &newnode);
	count_infiles(head, &newnode);
	count_outfiles(head, &newnode);
	count_heredoc(head, &newnode);
	return (newnode);
}
int	aftr_pipe(t_token **head, t_parce *newnode, t_env *env, int x)
{
	while ((*head) && (*head)->type != PIPE)
	{
		if ((*head)->type != WORD)
		{
			if (infile_data(env, head, newnode, &x) == 1 \
			|| outfile_data(env, head, newnode, &x) == 1 \
			|| heredoc_data(env, head, newnode, &x) == 1)
				return (1);
		}
		else
		{
			if (cmd_data(env, *head, newnode, &x) == 1)
				return (1);
		}
		(*head) = (*head)->next;
	}
	return (0);
}
void	pars_ing(t_parce **lst, t_env *env, t_token *head)
{
	t_parce *newnode;
	int check;
	t_parce *tmp;
	
	check = 0;	
	if (head->type == PIPE)
		return (ft_lstclear(head), update_status(env));
	newnode = data_alloc(head);
	if (aftr_pipe(&head, newnode, env, check) == 1)
		return (ft_lstclear(head));
	parse_add_back(lst, newnode);

	while (head)
	{
		if (head->type == PIPE && head->next)
		{
			head = head->next;
			check = 1;
			newnode = data_alloc(head);
			if (aftr_pipe(&head, newnode, env, check) == 1)
				return (ft_lstclear(head));
			parse_add_back(lst, newnode); // node --> pipe --> node 
		}
		else
			return (ft_lstclear(head), update_status(env));
	}
}
