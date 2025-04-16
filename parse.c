#include "minishell.h"

int is_spcharc(char c)
{
	if ((c == '|' || c == '>'
	|| c == '&' || c == '(' || c == ')' 
	|| c == '#' || c == ';' || c == '<'))
		return (1);
	return (0);
}
int	skip_space(char *s)
{
	int i;
	i = 0;
	while (s[i] && ft_isspace(s[i]) == 1)
		i++;
	return (i - 1);
}

int	handle_pipe(char *s, t_token **head)
{
	
	t_token *new;
	if (s[0] == '|')
	{	
		new = ft_lstnew(ft_strdup("|"));
		new->type = TOKEN_PIPE;
		ft_lstadd_back(head, new);
		// printf("pipe: [%s]\n", new->value);
		return (1);
	}
	return (0);
}



