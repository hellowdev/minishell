#include "../minishell.h"

void	ft_lstclear(t_token *lst)
{
    if (!lst)
		return ;

    t_token *tmp;
	tmp = lst;
    
    while (tmp)
    {
        tmp = tmp->next;
		free(lst->value);
		free(lst);
        lst = tmp;
    }
}
void	doubfree(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
// void	free_doublst(t_parce *head)
// {
// 	if (!head)
// 		return ;

//     t_parce *tmp;
// 	tmp = head;
    
//     while (tmp)
//     {
//         tmp = tmp->next;
// 		free(head.);
// 		doubfree(head);
// 		free(lst);
//         lst = tmp;
//     }
// }
