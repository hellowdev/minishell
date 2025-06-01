/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfartah <sfartah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:42:48 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/31 15:03:13 by sfartah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmd(t_token *head, t_parce *newnode, int *status, t_env *env)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = head;
	while (head && head->type != PIPE)
	{
		if (head->type != WORD && head->next)
			head = head->next;
		else if (head->type == WORD)
			i++;
		head = head->next;
	}
	if (i)
	{
		newnode->cmd = malloc(sizeof(char *));
		newnode->cmd[0] = NULL;
		get_cmd(tmp, newnode, status, env);
	}
	return (0);
}

int	count_infiles(t_token *head, t_parce *newnode, int *status, t_env *env)
{
	int		i;
	t_token	*tmp;

	tmp = head;
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == RED_IN)
			i++;
		head = head->next;
	}
	if (i)
	{
		newnode->infiles = malloc((i + 1) * sizeof(char *));
		if (get_infile(tmp, newnode, status, env))
			return (1);
	}
	return (0);
}

int	count_outfiles(t_token *head, t_parce *newnode, int *status, t_env *env)
{
	int		i;
	t_token	*tmp;

	tmp = head;
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == RED_OUT || head->type == APPEND)
			i++;
		head = head->next;
	}
	if (i)
	{
		(newnode)->outfiles = malloc((i + 1) * sizeof(char *));
		(newnode)->append = malloc(i * sizeof(bool));
		if (get_outfile(tmp, newnode, status, env))
			return (1);
	}
	return (0);
}

int	count_heredoc(t_token *head, t_parce *newnode, int *status)
{
	int		i;
	t_token	*tmp;

	tmp = head;
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == HEREDOC)
			i++;
		head = head->next;
	}
	if (i)
	{
		newnode->heredoc = malloc((i + 1) * sizeof(char *));
		if (get_herdoc(tmp, newnode, status))
			return (1);
	}
	return (0);
}
