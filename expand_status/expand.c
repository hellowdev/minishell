/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:51:04 by ychedmi           #+#    #+#             */
/*   Updated: 2025/07/02 19:58:18 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_exp(char *s, char **value)
{
	int		i;
	int		len;
	char	*notexp;

	len = 0;
	i = 0;
	if (s[i] && s[i] == '$' && special_char(s[i + 1]) == 1 && s[i + 1] != '?')
	{
		i++;
		len = strlen_dol(&s[i]);
		len++;
		notexp = ft_substr(s, 0, len);
		*value = ft_strjoin(*value, notexp);
		free_null(&notexp);
	}
	return (len);
}

int	relative_path(char *s, t_env *env, char **value, int ifdoc)
{
	int		i;
	char	*home;

	i = 0;
	if (ifdoc == 0)
	{
		if (s[i] == '~' && !s[i + 1])
		{
			i = 1;
			home = env_searsh(env, "HOME");
			*value = ft_strjoin(*value, home);
			free_null(&home);
		}
		else if (s[i] == '~' && s[i + 1] == '/')
		{
			i = 2;
			home = env_searsh(env, "HOME");
			*value = ft_strjoin(*value, home);
			free_null(&home);
		}
	}
	return (i);
}

int	expand(char *s, char **value, t_env *env, int ifdoc)
{
	int		i;
	int		len; 
	char	*name;
	char	*retenv;

	len = 0;
	i = 0;
	len = relative_path(s, env, value, ifdoc);
	if (s[i] && s[i] == '$' && special_char(s[i + 1]) == 0)
	{
		len = check_dol_sp(&s[i]);
		name = ft_substr(s, i + 1, len - 1);
		retenv = env_searsh(env, name);
		*value = ft_strjoin(*value, retenv);
		free_null(&name);
		free_null(&retenv);
	}
	else if (s[i] && s[i] == '$' && s[i + 1] == '?')
	{
		name = ft_itoa(g_status);
		*value = ft_strjoin(*value, name);
		len = 2;
		free_null(&name);
	}
	return (len);
}

int	simple_word(char *s, char **value)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	len = 0;
	if (s[i] && s[i] != '$' && s[i] != 34 && s[i] != 39)
	{
		len = strlen_dol(&s[i]);
		word = ft_substr(s, i, len);
		*value = ft_strjoin(*value, word);
		free_null(&word);
	}
	return (len);
}

char	*expand_status(char *str, t_env *env, bool inside_dq)
{
	int		j;
	char	*value;

	value = NULL;
	j = 0;
	while (str[j])
	{
		if (!inside_dq)
			j += sing_qt(&str[j], &value);
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
		j += doub_qt(&str[j], &value, &inside_dq);
		j += not_exp(&str[j], &value);
		j += expand(&str[j], &value, env, 0);
		j += simple_word(&str[j], &value);
	}
	return (value);
}
