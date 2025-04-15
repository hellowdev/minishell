#include "../minishell.h"

t_token *ft_lstlast(t_token *lst)
{
    while (lst->next)
        lst = lst->next;
    return (lst);
}
