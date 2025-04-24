#include "../minishell.h"

int	infile_data(t_env *env, t_token **head, t_parce *newnode, int *x)
{
	static int i;
	if (*x == 1)
	{
		*x = 0;
		i = 0;
	}
	if ((*head)->next && (*head)->type == RED_IN \
	&& valid_word((*head)->next) == 1)
	{
		newnode->infiles[i] = ft_strdup((*head)->next->value);
		newnode->infiles[i + 1] = NULL;
		(*head) = (*head)->next;
		i++;
	}
	else if ((!(*head)->next || valid_word((*head)->next) != 1) \
	&& (*head)->type == RED_IN)
		return (update_status(env), 1);
	return (0);
}
int	outfile_data(t_env *env, t_token **head, t_parce *newnode, int *x)
{
	static int i;
	if (*x == 1)
	{
		*x = 0;
		i = 0;
	}
	if ((*head)->next && ((*head)->type == RED_OUT \
	|| (*head)->type == APPEND) && valid_word((*head)->next) == 1)
	{
		newnode->outfiles[i] = ft_strdup((*head)->next->value);
		newnode->outfiles[i + 1] = NULL;
		if ((*head)->type == RED_OUT)
			newnode->append[i] = false;
		else if ((*head)->type == APPEND)
			newnode->append[i] = true;
		(*head) = (*head)->next;
		i++;
	}
	else if ((!(*head)->next || valid_word((*head)->next) != 1) \
	&& ((*head)->type == APPEND || (*head)->type == RED_OUT))
		return (update_status(env), 1);
	return (0);
}

int	heredoc_data(t_env *env, t_token **head, t_parce *newnode, int *x)
{
	static int i;
	if (*x == 1)
	{
		*x = 0;
		i = 0;
	}
	if ((*head)->next && (*head)->type == HEREDOC && valid_word((*head)->next) == 1)
	{
		newnode->heredoc[i] = ft_strdup((*head)->next->value);
		newnode->heredoc[i + 1] = NULL;
		i++;
		(*head) = (*head)->next;
	}
	else if ((!(*head)->next || valid_word((*head)->next) != 1) && (*head)->type == HEREDOC)
		return (update_status(env), 1);
	return (0);
}

int	cmd_data(t_env *env, t_token *head, t_parce *newnode, int *x)
{
	static int i;
	if (*x == 1)
	{
		*x = 0;
		i = 0;
		printf("[i : %d]\n", i);
	}
	if (valid_word(head) == 1)
	{
		newnode->cmd[i] = ft_strdup(head->value);
		newnode->cmd[i + 1] = NULL;
		i++;
	}
	else if (valid_word(head) != 1)
		return (update_status(env), 1);
	return (0);
}
