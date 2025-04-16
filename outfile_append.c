#include "minishell.h"

int	outfile_append(char *s, t_token **head)
{
	int i;
	i = 0;
	if (s[i] == '>' && s[i + 1] != '>')
		i += red_outfile(head);
	else if (s[i] == '>' && s[i + 1] == '>')
		i += append(head);
	return (i);
}

int	red_outfile(t_token **token)
{
    t_token *new;
	new = ft_lstnew(ft_strdup(">"));
	new->type = TOKEN_REDIRECT_OUT;
	ft_lstadd_back(token, new);
	// printf("outfile: [%s]\n", new->value);
	return (1);
}

int	append(t_token **token)
{
	t_token *new;
	new = ft_lstnew(ft_strdup(">>"));
	new->type = TOKEN_APPEND;
	ft_lstadd_back(token, new);
	// printf("append: [%s]\n", new->value);
	return (2);
}