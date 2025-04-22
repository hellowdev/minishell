#include "../minishell.h"

int count_cmd(t_token *head)
{
	int i;

	i = 0;
	while (head)
	{
		if (head->type == REDIRECT_IN || head->type == REDIRECT_OUT \
		|| head->type == HEREDOC || head->type == APPEND)
			head = head->next;
		else if (head->type == WORD)
			i++;
		head = head->next;
	}
	return (i);
}

int count_infiles(t_token *head)
{
	int i;

	i = 0;
	while (head)
	{
		if (head->type == REDIRECT_IN)
			i++;
		head = head->next;
	}    
	return(i);
}

int count_outfiles(t_token *head)
{
	int i;

	i = 0;
	while (head)
	{
		if (head->type == REDIRECT_OUT || head->type == APPEND)
			i++;
		head = head->next;
	}    
	return(i);
}

int count_heredoc(t_token *head)
{
	int i;

	i = 0;
	while (head)
	{
		if (head->type == HEREDOC)
			i++;
		head = head->next;
	}    
	return(i);
}
