#include "../minishell.h"

int count_cmd(t_token *head, t_parce *newnode, int *status, t_env *env)
{
	int i;
	t_token *tmp;

	i = 0;
	tmp = head;
	while (head && head->type != PIPE)
	{
		if (head->type != WORD && head->next)
			head = head->next;
		else if (head->type == WORD)
			i++;
		head = head->next;
	}// count how many cmds between pipes
	if (i)
	{
		newnode->cmd = malloc((i + 1) * sizeof(char *));
		get_cmd(tmp, newnode, status, env);
	}
	return (0);
}

int count_infiles(t_token *head, t_parce *newnode, int *status, t_env *env)
{
	int i;
	t_token *tmp;

	tmp = head;
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == RED_IN)
			i++;
		head = head->next;
	}// count how many infiles between pipes
	if (i)
	{
		newnode->infiles = malloc((i + 1) * sizeof(char *));
		if (get_infile(tmp, newnode, status, env))
			return (1);
	}
	return(0);
}

int count_outfiles(t_token *head, t_parce *newnode, int *status, t_env *env)
{
	int i;
	t_token *tmp;
	tmp = head;
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == RED_OUT || head->type == APPEND)
			i++;
		head = head->next;
	}// count how many outfiles between pipes
	if (i)
	{
		(newnode)->outfiles = malloc((i + 1) * sizeof(char *));
		(newnode)->append = malloc(i * sizeof(bool));
		if(get_outfile(tmp, newnode, status, env))
			return (1);
	}
	return(0);
}

int count_heredoc(t_token *head, t_parce *newnode, int *status)
{
	int i;
	t_token *tmp;
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
	return(0);
}
