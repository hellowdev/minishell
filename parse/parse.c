/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:10 by ychedmi           #+#    #+#             */
/*   Updated: 2025/04/23 22:52:08 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parce	*data_alloc(t_token *head)
{
	t_parce *newnode;
	int cmd;
	int infile;
	int outfile;
	int herdoc;
	
	newnode = malloc(sizeof(t_parce)); // alloc  all node
	if (!newnode)
        return NULL;
	newnode->next = NULL;
	cmd = count_cmd(head);
	infile = count_infiles(head);
	outfile = count_outfiles(head);
	herdoc = count_heredoc(head);
	if (cmd != 0)
		newnode->cmd = malloc((cmd + 1) * sizeof(char *));
	if (herdoc != 0)
		newnode->heredoc = malloc((herdoc + 1) * sizeof(char *));
	if (infile != 0)
		(newnode)->infiles = malloc((infile + 1) * sizeof(char *));
	if (outfile != 0)
	{
		(newnode)->outfiles = malloc((outfile + 1) * sizeof(char *));
		(newnode)->append = malloc(outfile * sizeof(bool));
	}
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
	check = 0;
	if (!head)
		return ;
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
			// printf("here\n");
		}
		else
			return (ft_lstclear(head), update_status(env));
		// if (head->next)
			// head = head->next;
		printf("here\n");
	}
}
