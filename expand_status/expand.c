/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:51:04 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/30 09:54:50 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strlen_dol(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' || s[i] == 34 || s[i] == 39)
			return (i);
		i++;
	}
	return (i);
}

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

int	expand(char *s, char **value, t_env *env, int status)
{
	int		i;
	int		checker; 
	char	*name;
	char	*retenv;

	checker = 0;
	i = 0;
	if (s[i] && s[i] == '$' && special_char(s[i + 1]) == 0)
	{
		checker = check_dol_sp(&s[i]);
		name = ft_substr(s, i + 1, checker - 1);
		retenv = env_searsh(env, name);
		*value = ft_strjoin(*value, retenv);
		free_null(&name);
		free_null(&retenv);
	}
	else if (s[i] && s[i] == '$' && s[i + 1] == '?')
	{
		name = ft_itoa(status);
		*value = ft_strjoin(*value, name);
		checker = 2;
		free_null(&name);
	}
	return (checker);
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

char	*expand_status(char *str, t_env *env, bool checker, int status)
{
	int		j;
	char	*value;

	value = NULL;
	j = 0;
	while (str[j])
	{
		if (checker == false)
			j += sing_qt(&str[j], &value);
		j += doub_qt(&str[j], &value, &checker);
		j += not_exp(&str[j], &value);
		j += expand(&str[j], &value, env, status);
		if (str[j] == 39 && checker == true)
		{
			value = ft_strjoin(value, "'");
			j++;
		}
		j += simple_word(&str[j], &value);
		if (str[j] == '$' && (str[j + 1] == '$' || !str[j + 1]))
		{
			value = ft_strjoin(value, "$");
			j++;
		}
	}
	return (value);
}
