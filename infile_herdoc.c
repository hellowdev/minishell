#include "minishell.h"

int	infile_heredoc(char *s, t_token **head)
{
	int i;
	i = 0;
	if (s && s[i] == '<' && s[i + 1] != '<')
		i += red_infile(head);
	else if (s && s[i] == '<' && s[i + 1] == '<')
		i += here_doc(head);
	return (i);
}

int	red_infile(t_token **token)
{	
	t_token *new;
	new = ft_lstnew(ft_strdup("<"));
	new->type = TOKEN_REDIRECT_IN;
	ft_lstadd_back(token, new);
	// printf("infile: [%s]\n", new->value);
	return (1);
}

int here_doc(t_token **token)
{
	t_token *new;
	new = ft_lstnew(ft_strdup("<<"));
	
	new->type = TOKEN_HEREDOC;
	ft_lstadd_back(token, new);
	// printf("heredoc: [%s]\n", new->value);
	return (2);

}


