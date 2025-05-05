#include "../minishell.h"

void	free_null(char **s)
{
	free(*s);
	*s = NULL;
}
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
void	free_doublst(t_parce *head)
{
	if (!head)
		return ;

    t_parce *tmp;
	tmp = head;
	
    while (tmp)
    {
        tmp = tmp->next;	
		free(head->append);
		doubfree(head->cmd);
		doubfree(head->infiles);
		doubfree(head->outfiles);
		doubfree(head->heredoc);
		free(head);
        head = tmp;
    }
}
void	doubfree(char **s)
{
	int i;
	if (!s)
		return ;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
void	free_env(t_env *head)
{
	 if (!head)
		return ;

    t_env *tmp;
	tmp = head;
    
    while (tmp)
    {
        tmp = tmp->next;
		free(head->name_env);
		free(head->value_env);
		free(head);
        head = tmp;
    }
}