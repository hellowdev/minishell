#include "../minishell.h"


t_token *ft_lstnew(void *content)
{
    t_token *newnode = (t_token *)malloc(sizeof(t_token));
    
    if (!newnode)
        return (NULL);

    newnode->value = content;
    newnode->next = NULL;

    return (newnode);
}
