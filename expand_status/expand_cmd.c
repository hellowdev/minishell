/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfartah <sfartah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:51:04 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/02 13:10:32 by sfartah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    **expand_cmd(char *s, t_env *env, int *len)
{
	char	*name;
	char	*retenv;
	char	**final_return;
	int		i;

	i = 0;
	final_return = NULL;
	if (s[i] && s[i] == '$' && special_char(s[i + 1]) == 0)
	{
		*len += check_dol_sp(&s[i]);
		name = ft_substr(s, i + 1, check_dol_sp(&s[i]) - 1);
		retenv = env_searsh(env, name);
		final_return = ft_split(retenv, 32);
		free_null(&name);
		free_null(&retenv);
	}
	else if (s[i] && s[i] == '$' && s[i + 1] == '?')
	{
		*len += 2;
		final_return = malloc(2 * sizeof(char *));
		*final_return = ft_itoa(status);
		final_return[1] = NULL;
	}
	return (final_return);
}

int	handle_expansion(char *str, char ***value, int *i, t_env *env)
{
	char	**ret;
	int		offset;
	int		len;

	offset = 0;
	ret = expand_cmd(str, env, &offset);
	len = double_len(ret);
	if (len > 1)
	{
		(*value)[*i] = ft_strjoin((*value)[*i], *ret);
		*value = ft_doubjoin(*value, ret + 1);
		*i += len - 1;
	}
	else if (len == 1)
		(*value)[*i] = ft_strjoin((*value)[*i], *ret);
	doubfree(ret);
	return (offset);
}

int	handle_special_cases(char *str, char **curr, bool inside_dq)
{
	int	offset;

	offset = 0;
	if (str[offset] == 39 && inside_dq)
	{
		*curr = ft_strjoin(*curr, "'");
		offset++;
	}
	if (str[offset] == '$' && (str[offset + 1] == '$' || !str[offset + 1]))
	{
		*curr = ft_strjoin(*curr, "$");
		offset++;
	}
	return (offset);
}

char	**word_to_cmd(char *str, t_env *env, bool inside_dq)
{
	int		i;
	int		j;
	char	**value;

	value = malloc(2 * sizeof(char *));
	if (!value)
		return (NULL);
	value[0] = NULL;
	value[1] = NULL;
	i = 0;
	j = 0;
	while (str[j])
	{
		j += doub_qt(&str[j], &value[i], &inside_dq);
		j += not_exp(&str[j], &value[i]);
		j += simple_word(&str[j], &value[i]);
		if (!inside_dq)
			j += sing_qt(&str[j], &value[i]);
		j += handle_special_cases(&str[j], &value[i], inside_dq);
		j += handle_expansion(&str[j], &value, &i, env);
	}
	return (value);
}

// char	**word_to_cmd(char *str, t_env *env, bool inside_dq)
// {
// 	int		j;
// 	int     i;
// 	char	**value;
// 	char	**ret_expand;

// 	value = malloc(2 * sizeof(char *));
// 	value[0] = NULL;
// 	value[1] = NULL;
// 	j = 0;
// 	i = 0;
// 	while (str[j])
// 	{
// 		j += doub_qt(&str[j], &value[i], &inside_dq);
// 		j += not_exp(&str[j], &value[i]);
// 		j += simple_word(&str[j], &value[i]);
// 		if (!inside_dq)
// 			j += sing_qt(&str[j], &value[i]);
// 		if (str[j] == 39 && inside_dq)
// 		{
// 			value[i] = ft_strjoin(value[i], "'");
// 			j++;
// 		}
// 		if (str[j] == '$' && (str[j + 1] == '$' || !str[j + 1]))
// 		{
// 			value[i] = ft_strjoin(value[i], "$");
// 			j++;
// 		}
// 		ret_expand = expand_cmd(&str[j], env, &j);
// 		if (double_len(ret_expand) > 1)
// 		{
// 			value[i] = ft_strjoin(value[i], *ret_expand);
// 			value = ft_doubjoin(value, ret_expand + 1);
// 			i += double_len(ret_expand) - 1;
// 		}
// 		else if (double_len(ret_expand) == 1)
// 			value[i] = ft_strjoin(value[i], *ret_expand);
// 		doubfree(ret_expand);
// 	}
// 	return (value);
// }