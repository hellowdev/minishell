#include "../minishell.h"

void	ft_lstdelone(t_env *lst)
{
	if (!lst)
		return ;
	free(lst->name_env);
	free(lst->value_env);
	free(lst);
}
