/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:51:04 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/04 13:29:38 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rel_path(char *s, t_env *env, char ***value)
{
	int	i;

	i = 0;
	if (s[i] == '~' && (!s[i + 1] || s[i + 1] == '/'))
	{
		i = 1;
		*value = malloc(2 * sizeof(char *));
		(*value)[0] = env_searsh(env, "HOME");
		(*value)[1] = NULL;
	}
	return (i);
}


char	**get_value(char *s, t_env *env, int *len, int *check)
{
	char	*name;
	char	*retenv;
	char	**final_return;
	int		i;

	i = 0;
	final_return = NULL;
	*len += rel_path(s, env, &final_return);
	if (s[i] && s[i] == '$' && special_char(s[i + 1]) == 0)
	{
		*len += check_dol_sp(&s[i]);
		name = ft_substr(s, i + 1, check_dol_sp(&s[i]) - 1);
		retenv = env_searsh(env, name);
		*check = export_space(retenv);
		final_return = ft_split(retenv, 32);
		return (free_null(&name), free_null(&retenv), final_return);
	}
	else if (s[i] && s[i] == '$' && s[i + 1] == '?')
	{
		*len += 2;
		final_return = malloc(2 * sizeof(char *));
		*final_return = ft_itoa(g_status);
		final_return[1] = NULL;
	}
	return (final_return);
}


int	expand_cmd(char ***value, char *str, t_env *env, int *i)
{
	char	**ret;
	int		check;
	int		j;
	char	**ptr;

	j = 0;
	check = 0;
	ptr = ft_calloc(2 , sizeof(char *));
	ret = get_value(str, env, &j, &check);
	if (check == 1 || double_len(ret) > 1)
	{
		(*value)[*i] = ft_strjoin((*value)[*i], *ret);
		if (double_len(ret) == 1)
			return (ret = ft_special_join(ret, ptr), \
			*value = ft_special_join(*value, &ret[1]), \
			*i += double_len(ret), doubfree(ret), j);
		else
		{	
			*i += double_len(ret) - 1;
			*value = ft_doubjoin(*value, &ret[1]);
		}
	}
	else if (double_len(ret) == 1)
		(*value)[*i] = ft_strjoin((*value)[*i], *ret);
	return (doubfree(ret), j);
}

int	edge_case(char *str, char **value, bool inside_dq)
{
	int	j;

	j = 0;
	if (str[j] == 39 && inside_dq)
	{
		*value = ft_strjoin(*value, "'");
		j++;
	}
	if (str[j] == '$' && (str[j + 1] == '$' || !str[j + 1]))
	{
		*value = ft_strjoin(*value, "$");
		j++;
	}
	return (j);
}

char	**word_to_cmd(char *str, t_env *env, bool inside_dq)
{
	int		j;
	int		i;
	char	**value;

	value = ft_calloc(2, sizeof(char *));
	j = 0;
	i = 0;
	while (str[j])
	{
		j += doub_qt(&str[j], &value[i], &inside_dq);
		j += not_exp(&str[j], &value[i]);
		if (!inside_dq)
			j += sing_qt(&str[j], &value[i]);
		j += edge_case(&str[j], &value[i], inside_dq);
		j += expand_cmd(&value, &str[j], env, &i);
		j += simple_word(&str[j], &value[i]);
	}
	return (value);
}
