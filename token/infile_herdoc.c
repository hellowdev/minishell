/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:03 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/02 11:33:51 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	infile_heredoc(char *s, t_token **head)
{
	int i;
	i = 0;
	if (s && s[i] == '<' && s[i + 1] != '<')
		i += red_infile(head);
	else if (s && s[i] == '<' && s[i + 1] == '<')
		i += here_doc(head);
	return (i);
}

int	red_infile(t_token **token)
{	
	t_token *new;
	new = ft_lstnew(ft_strdup("<"), RED_IN);
	ft_lstadd_back(token, new);
	return (1);
}

int here_doc(t_token **token)
{
	t_token *new;
	new = ft_lstnew(ft_strdup("<<"), HEREDOC);	
	ft_lstadd_back(token, new);
	return (2);
}


