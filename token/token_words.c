/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:14 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/30 09:26:37 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	doub_quote(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != 34)
		i++;
	return (i);
}

int	sing_quote(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != 39)
		i++;
	return (i);
}

int	ft_lenspace(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]) == 0 \
	&& s[i] != '<' && s[i] != '>' && s[i] != '|')
	{
		if (s[i] == 34)
			i += doub_quote(&s[i]);
		else if (s[i] == 39)
			i += sing_quote(&s[i]);
		i++;
	}
	return (i);
}

int	words(char *s, t_token **token)
{
	t_token	*new;
	int		ret;

	ret = ft_lenspace(s);
	new = ft_lstnew(ft_substr(s, 0, ret), WORD);
	ft_lstadd_back(token, new);
	return (ret); 
}

int	check_words(char *s, t_token **head)
{
	int	i;

	i = 0;
	if (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>' && s[i] != '|')
		i += words(&s[i], head);
	return (i);
}
