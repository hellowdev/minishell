#include "../minishell.h"

void	infile_data(t_env *env, t_token *head, t_parce *newnode)
{
	static int i;
	
	if (head->type == REDIRECT_IN && valid_word(head->next) == 1)
	{
		newnode->infiles[i] = ft_strdup(head->next->value);
		head = head->next;
		i++;
	}
	else if (head->type == REDIRECT_IN && valid_word(head->next) != 1)
	{
		update_status(env);
		write(2, "syntax error near unexpected token", 35);
		return (ft_lstclear(head)/*, free cmd , free outfiles, free infiles, free appends, free heredocs*/);
	}
	
}
void	outfile_data(t_env *env, t_token *head, t_parce *newnode)
{
	static int i;

	if ((head->type == REDIRECT_OUT || head->type == APPEND) && valid_word(head->next) == 1)
	{
		newnode->outfiles[i] = ft_strdup(head->next->value);
		head = head->next;
		i++;
		if (head->type == REDIRECT_OUT)
			newnode->append[i] = false;
		else if (head->type == APPEND)
			newnode->append[i] = true;
	}
	else if (head->type == REDIRECT_OUT && valid_word(head->next) != 1)
	{
		
	}
}

void	heredoc_data(t_env *env, t_token *head, t_parce *newnode)
{
	static int i;

	if (head->type == HEREDOC && valid_word(head->next) == 1)
	{
		newnode->heredoc[i] = ft_strdup(head->next->value);
		i++;
		head = head->next;
	}
	else if (head->type == HEREDOC && valid_word(head->next) != 1)
	{
		
	}
}

void	cmd_data(t_env *env, t_token *head, t_parce *newnode)
{
	static int i;
	// value WORD == echo -> -n -> "test"
	// cmd == 3
	if (head->type == WORD && valid_word(head->value) == 1)
	{
		newnode->cmd[i] = ft_strdup(head->value);
		i++;
	}
	else if (head->type == HEREDOC && valid_word(head->next) != 1)
	{
		
	}
}
