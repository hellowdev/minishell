#include "../minishell.h"

int	count_cmd(t_token *head)
{
	int		i;
	int		j;
	t_token	*tmp;

	tmp = head;
	i = 0;
	j = 0;
	while (head && head->type != PIPE)
	{
		if ((head->type == RED_IN )\
		|| (head->type == RED_OUT )\
		|| (head->type == APPEND ))
			i++;
		head =  head->next;	
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			j++;
		tmp = tmp->next;
	}
	return (j - i + 1);
}

int count_infiles(t_token *head)
{
	int i;

	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == RED_IN)
			i++;
		head = head->next;
	}    
	return(i);
}

int count_outfiles(t_token *head)
{
	int i;

	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == RED_OUT || head->type == APPEND)
			i++;
		head = head->next;
	}    
	return(i);
}

int count_heredoc(t_token *head)
{
	int i;

	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == HEREDOC)
			i++;
		head = head->next;
	}    
	return(i);
}
