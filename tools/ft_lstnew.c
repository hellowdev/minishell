/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:33:52 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/30 09:30:58 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstnew(void *content, t_type type)
{
	t_token	*newnode;

	newnode = malloc(sizeof(t_token));
	if (!newnode)
		return (NULL);
	newnode->value = content;
	newnode->type = type;
	newnode->next = NULL;
	return (newnode);
}

t_env	*lstnew_env(void *name, void *value)
{
	t_env	*newnode;

	newnode = malloc(sizeof(t_env));
	if (!newnode)
		return (NULL);
	newnode->name_env = name;
	newnode->value_env = value;
	newnode->next = NULL;
	return (newnode);
}
