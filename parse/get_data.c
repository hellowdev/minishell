/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:46:27 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 18:55:11 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_infile(t_token *head, t_parce *newnode, t_env *env)
{
	int	c;

	c = 0;
	while (head && head->type != PIPE)
	{
		if (head->next && head->type == RED_IN \
		&& head->next->type == WORD)
		{
			newnode->infiles[c] = \
			expand_status(head->next->value, env, false);
			c++;
		}
		else if ((!head->next || head->next->type != WORD) \
		&& head->type == RED_IN)
		{
			newnode->infiles[c] = NULL;
			return (update_status("<"), 1);
		}
		head = head->next;
	}
	newnode->infiles[c] = NULL;
	return (0);
}

int	get_outfile(t_token *head, t_parce *newnode, t_env *env)
{
	int	c;

	c = 0;
	while (head && head->type != PIPE)
	{
		if (head->next && (head->type == RED_OUT \
		|| head->type == APPEND) && head->next->type == WORD)
		{
			newnode->outfiles[c] = \
			expand_status(head->next->value, env, false);
			if (head->type == RED_OUT)
				newnode->append[c] = false;
			else if (head->type == APPEND)
				newnode->append[c] = true;
			c++;
		}
		else if ((head->type == APPEND || head->type == RED_OUT) \
		&& (!head->next || head->next->type != WORD))
			return (newnode->outfiles[c] = NULL, update_status(">"), 1);
		head = head->next;
	}
	newnode->outfiles[c] = NULL;
	return (0);
}

int	get_herdoc(t_token *head, t_parce *newnode)
{
	int	c;

	c = 0;
	while (head && head->type != PIPE)
	{
		if (head->next && head->type == HEREDOC && head->next->type == WORD)
		{
			newnode->heredoc[c] = \
			deljoin(head->next->value, &newnode->check_qt);
			c++;
		}
		else if (head->type == HEREDOC && \
		(!head->next || head->next->type != WORD))
			return (newnode->heredoc[c] = NULL, update_status("<<"), 1);
		head = head->next;
	}
	newnode->heredoc[c] = NULL;
	return (0);
}

int	get_cmd(t_token *head, t_parce *newnode, t_env *env)
{
	char	**word;

	while (head && head->type != PIPE)
	{
		if (head->type != WORD && head->next)
			head = head->next;
		else if (head->type == WORD)
		{
			word = word_to_cmd(head->value, env, false);
			newnode->cmd = ft_doubjoin(newnode->cmd, word);
			doubfree(word);
		}
		head = head->next;
	}
	return (0);
}
