#include "../minishell.h"

int get_infile(t_token *head, t_parce *newnode, t_env *env)
{
    int c;
	c = 0;
	while (head && head->type != PIPE)
	{
		if (head->next && head->type == RED_IN \
		&& head->next->type == WORD)
		{
			newnode->infiles[c] = ft_strdup(head->next->value);
			printf("[infile: %s]\n", newnode->infiles[c]);
			c++;
		}
		else if ((!head->next || head->next->type != WORD) \
		&& head->type == RED_IN)
		{
			newnode->infiles[c] = NULL;
			return (update_status(env), 1);
		}
		head = head->next;
	}
	newnode->infiles[c] = NULL;
	return (0);
}


int	get_outfile(t_token *head, t_parce *newnode, t_env *env)
{
	int c;
	c = 0;
	while (head && head->type != PIPE)
	{
		if (head->next && (head->type == RED_OUT \
		|| head->type == APPEND) && head->next->type == WORD)
		{
			newnode->outfiles[c] = ft_strdup(head->next->value);
			printf("[outfile: %s]\n", newnode->outfiles[c]);
			if (head->type == RED_OUT)
				newnode->append[c] = false;
			else if (head->type == APPEND)
				newnode->append[c] = true;
			c++;
		}
		else if ((head->type == APPEND || head->type == RED_OUT) \
		&& (!head->next || head->next->type != WORD))
			return (newnode->outfiles[c] = NULL ,update_status(env), 1);
		head = head->next;
	}
	newnode->outfiles[c] = NULL;
	return (0);
}

int	get_herdoc(t_token *head, t_parce *newnode, t_env *env)
{
	int c;
	c = 0;
	while (head && head->type != PIPE)
	{
		if (head->next && head->type == HEREDOC && head->next->type == WORD)
		{
			newnode->heredoc[c] = ft_strdup(head->next->value);
			printf("[heredoc: %s]\n", newnode->heredoc[c]);
			c++;
		}
		else if (head->type == HEREDOC && (!head->next || head->next->type != WORD))
			return (newnode->heredoc[c] = NULL, update_status(env), 1);
		head = head->next;
	}
	newnode->heredoc[c] = NULL;
	return (0);
}

int	get_cmd(t_token *head, t_parce *newnode, t_env *env)
{
	int c;
	c = 0;
	(void)env;
	while (head && head->type != PIPE)
	{
		if (head->type != WORD && head->next)
			head = head->next;
		else if (head->type == WORD)
		{
			newnode->cmd[c] = ft_strdup(head->value);
			printf("[cmd: %s]\n", newnode->cmd[c]);
			c++;
		}
		head = head->next;
	}
	newnode->cmd[c] = NULL;
	return (0);
}
