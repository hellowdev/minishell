#include "../minishell.h"

int get_infile(t_token *head, int i, t_parce *newnode, t_env *env)
{
    int c;
	c = 0;
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->next && head->type == RED_IN \
		&& valid_word(head->next) == 1)
		{
			newnode->infiles[c] = ft_strdup(head->next->value);
			// printf("[infile: %s]\n", newnode->infiles[c]);
			c++;
		}
		else if ((!head->next || valid_word(head->next) != 1) \
		&& head->type == RED_IN)
			return (update_status(env), 1/*free_all(newnode)*/);
		head = head->next;
	}
	newnode->infiles[c] = NULL;
	return (0);
}

int	get_cmd(t_token *head, int i, t_parce *newnode, t_env *env)
{
	int c;

	c = 0;
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type != WORD && head->next)
			head = head->next;
		else if (head->type == WORD && valid_word(head) != 1)
			return (update_status(env), 1);
		else if (head->type == WORD && valid_word(head) == 1)
		{
			newnode->cmd[c] = ft_strdup(head->value);
			// printf("[cmd: %s]\n", newnode->cmd[c]);
			c++;
		}
		head = head->next;
	}
	newnode->cmd[c] = NULL;
	return (0);
}

int	get_outfile(t_token *head, int i, t_parce *newnode, t_env *env)
{
	int c;

	c = 0;
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->next && (head->type == RED_OUT \
		|| head->type == APPEND) && valid_word(head->next) == 1)
		{
			newnode->outfiles[c] = ft_strdup(head->next->value);
			// printf("[outfile: %s]\n", newnode->outfiles[c]);
			if (head->type == RED_OUT)
				newnode->append[c] = false;
			else if (head->type == APPEND)
				newnode->append[c] = true;
			c++;
		}
		else if ((!head->next || valid_word(head->next) != 1) \
		&& (head->type == APPEND || head->type == RED_OUT))
			return (update_status(env), 1);
		head = head->next;
	}
	newnode->outfiles[c] = NULL;
	return (0);
}

int	get_herdoc(t_token *head, int i, t_parce *newnode, t_env *env)
{
	int c;

	c = 0;
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->next && head->type == HEREDOC && valid_word(head->next) == 1)
		{
			newnode->heredoc[c] = ft_strdup(head->next->value);
			// printf("[heredoc: %s]\n", newnode->heredoc[c]);
			c++;
		}
		else if ((!head->next || valid_word(head->next) != 1) && head->type == HEREDOC)
			return (update_status(env), 1);
		head = head->next;
	}
	newnode->heredoc[c] = NULL;
	return (0);
}
