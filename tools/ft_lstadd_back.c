#include "../minishell.h"

void ft_lstadd_back(t_token **lst, t_token *new)
{
	if (!*lst || !new)
		return ;
	t_token *last = ft_lstlast(*lst);
	last->next = new;
}
