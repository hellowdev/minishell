#include "../minishell.h"

int count_cmd(t_token *head, t_parce *newnode)
{
	int i;
	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type != WORD && head->next)
			head = head->next;
		else if (head->type == WORD)
			i++;
		head = head->next;
	}
	newnode->cmd = malloc((i + 1) * sizeof(char *));

	return (i);
}

int count_infiles(t_token *head, t_parce *newnode)
{
	int i;

	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == RED_IN)
			i++;
		head = head->next;
	}
	newnode->infiles = malloc((i + 1) * sizeof(char *));
	// function get data inside
	return(i);
}

int count_outfiles(t_token *head, t_parce *newnode)
{
	int i;

	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == RED_OUT || head->type == APPEND)
			i++;
		head = head->next;
	}
	(newnode)->outfiles = malloc((i + 1) * sizeof(char *));
	(newnode)->append = malloc(i * sizeof(bool));
	return(i);
}

int count_heredoc(t_token *head, t_parce *newnode)
{
	int i;

	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == HEREDOC)
			i++;
		head = head->next;
	}
	newnode->heredoc = malloc((i + 1) * sizeof(char *));
	
	return(i);
}
