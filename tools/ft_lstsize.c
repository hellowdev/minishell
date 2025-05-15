#include "../minishell.h"

int ft_lstsize(t_parce *lst)
{
    int i;
    i = 0;
    if(!lst)
        return 0;
    while (lst)
    {
        lst = lst->next;
        i++;
    }
    return (i);
}
