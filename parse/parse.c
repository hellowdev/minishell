/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:10 by ychedmi           #+#    #+#             */
/*   Updated: 2025/04/23 18:58:08 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	data_alloc(t_token *head, t_parce **newnode)
{
	int cmd;
	int infile;
	int outfile;
	int herdoc;
	
	*newnode = malloc(sizeof(t_parce)); // alloc  all node
	if (!*newnode)
        return ;
	(*newnode)->next = NULL;
	cmd = count_cmd(head);
	infile = count_infiles(head);
	outfile = count_outfiles(head);
	herdoc = count_heredoc(head);
	if (cmd != 0)
		(*newnode)->cmd = malloc((cmd + 1) * sizeof(char *));
	if (herdoc != 0)
		(*newnode)->heredoc = malloc((herdoc + 1) * sizeof(char *));
	if (infile != 0)
		(*newnode)->infiles = malloc((infile + 1) * sizeof(char *));
	if (outfile != 0)
	{
		(*newnode)->outfiles = malloc((outfile + 1) * sizeof(char *));
		(*newnode)->append = malloc(outfile * sizeof(bool));
	}
	// printf("in alloc func\n");
}
int	aftr_pipe(t_token **head, t_parce *newnode, t_env *env)
{
	while ((*head))
	{
		if ((*head)->type != WORD)
		{
			if (infile_data(env, head, newnode) == 1 \
			|| outfile_data(env, head, newnode) == 1 \
			|| heredoc_data(env, head, newnode) == 1)
				return (1);
		}
		else
		{
			if (cmd_data(env, *head, newnode) == 1)
				return (1);
		}
		(*head) = (*head)->next;
		// printf("in while\n");
	}
	return (0);
}
void	pars_ing(t_parce **lst, t_env *env, t_token *head)
{
	t_parce *newnode;

	if (head->type == PIPE)
		return (ft_lstclear(head), update_status(env));
	data_alloc(head, &newnode);
	if (aftr_pipe(&head, newnode, env) == 1)
		return (ft_lstclear(head));
	parse_add_back(lst, newnode);
	while (head)
	{
		if (head->type == PIPE && head->next)
		{
			head = head->next;
			data_alloc(head, &newnode);
			if (aftr_pipe(&head, newnode, env) == 1)
				return (ft_lstclear(head));
			parse_add_back(lst, newnode); // node --> pipe --> node 
		}
		else
			return (ft_lstclear(head), update_status(env));
		head = head->next;
	}
}
