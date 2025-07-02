/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:24:56 by ychedmi           #+#    #+#             */
/*   Updated: 2025/07/02 20:16:21 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	take_single(char *s, char **str)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	if (s[i] == 39)
	{
		i = 1;
		if (s[i] == 39 && s[i + 1] != '\0')
			return (2);
		else if (s[i] == 39 && s[i + 1] == '\0')
			return (tmp1 = ft_strdup(""), *str = \
			ft_strjoin(*str, tmp1), free_null(&tmp1), 2);
		while (s[i] && s[i] != 39)
			i++;
		tmp2 = ft_substr(s, 0, i + 1);
		*str = ft_strjoin(*str, tmp2);
		return (free_null(&tmp2), i + 1);
	}
	return (i);
}

int	take_qoute(char *s, char **str, bool *inside_dq)
{
	int		i;
	char	*tmp;

	i = 0;
	if (s[i] == 34)
	{
		i = 1;
		if (s[i] == 34 && s[i + 1] != '\0')
			return (2);
		else if (s[i] == 34 && s[i + 1] == '\0')
		{
			tmp = ft_strdup("");
			return (*str = ft_strjoin(*str, tmp), free_null(&tmp), 2);
		}
		if (*inside_dq == true)
			*inside_dq = false;
		else
			*inside_dq = true;
		*str = ft_strjoin(*str, "\"");
		return (1);
	}
	return (i);
}

char	*expand_joined(char *str, t_env *env, bool inside_dq)
{
	int		j;
	char	*value;

	value = NULL;
	j = 0;
	while (str[j])
	{
		if (!inside_dq)
			j += take_single(&str[j], &value);
		if (str[j] == 39 && inside_dq)
		{
			value = ft_strjoin(value, "'");
			j++;
		}
		if (str[j] == '$' && (str[j + 1] == '$' || !str[j + 1]))
		{
			value = ft_strjoin(value, "$");
			j++;
		}
		j += take_qoute(&str[j], &value, &inside_dq);
		j += not_exp(&str[j], &value);
		j += expand(&str[j], &value, env, 0);
		j += simple_word(&str[j], &value);
	}
	return (value);
}

char	**splited_word(char *str, t_env *env)
{
	char	*joined_str;
	char	**splited_str;

	joined_str = expand_joined(str, env, false);
	splited_str = ft_salma_split(joined_str, 32);
	return (free_null(&joined_str), splited_str);
}
