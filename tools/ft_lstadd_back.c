#include "../minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*back;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	back = *lst;
	while (back->next)
		back = back->next;
	back->next = new;
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*back;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	back = *lst;
	while (back->next)
		back = back->next;
	back->next = new;
}