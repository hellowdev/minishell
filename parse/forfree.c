/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forfree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:01:15 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/30 09:06:47 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_null(char **s)
{
	free(*s);
	*s = NULL;
}

void	ft_lstclear(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		free(lst->value);
		free(lst);
		lst = tmp;
	}
}

void	free_doublst(t_parce **head)
{
	t_parce	*tmp;

	if (!(*head))
		return ;
	tmp = (*head);
	while (tmp)
	{
		tmp = tmp->next;
		free((*head)->append);
		doubfree((*head)->cmd);
		doubfree((*head)->infiles);
		doubfree((*head)->outfiles);
		doubfree((*head)->heredoc);
		free((*head));
		(*head) = tmp;
	}
	*head = NULL;
}

void	doubfree(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	free_env(t_env *head)
{
	t_env	*tmp;

	if (!head)
		return ;
	tmp = head;
	while (tmp)
	{
		tmp = tmp->next;
		free(head->name_env);
		free(head->value_env);
		free(head);
		head = tmp;
	}
}
