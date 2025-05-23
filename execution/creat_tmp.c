/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:12:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/23 13:47:45 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	doc_word(char *s, char **value)
{
	int i;
	int len;
	char *word;

	i = 0;
	len = 0;
	if (s[i] != '$')
	{
		len = strlen_herdoc(&s[i]);
		word = ft_substr(s ,i ,len);
		*value = ft_strjoin(*value, word);
		free_null(&word);
	}
	return (len);
}

char	*expand_doc(char *str, t_env *env, int status)
{
	int j;
	char *value;

	value = NULL;
	j = 0;
	while (str[j])
	{
		
		j += not_exp(&str[j], &value);
		j += expand(&str[j], &value, env, status);
		j += doc_word(&str[j], &value);
		if (str[j] == '$' && (str[j + 1] == '$' || !str[j + 1]))
		{
			value = ft_strjoin(value, "$");
			j++;
		}
	}
	free_null(&str);
	return (value);
}

char	*file_name(int index)
{
	char	*ret;
	char	*str;

	str = ft_itoa(index);
	ret = ft_strjoin(ft_strdup("/tmp/"), str);
	free_null(&str);
	return (ret);
}

void	get_lineee(char *heredoc, int fd, bool quoted, t_expand *stock)
{
	char *line;

	line = NULL;
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || ft_strcm_doc(line, heredoc) == 0)
			return free_null(&line);
		if (!quoted)
			line = expand_doc(line, stock->env, stock->status);
		write(fd, line, ft_strlen(line));
		free_null(&line);
	}
	return ;
}

void	creat_file(char **heredoc, bool quoted, int index, t_expand *stock)
{
	char	*file;
	char	*line;
	int	i;
	int	fd;

	i = 0;
	file = NULL;
	line = NULL;
	file = file_name(index);
	while (heredoc[i])
	{
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd < 0)
			return ;
		get_lineee(heredoc[i], fd, quoted, stock);
		close(fd);
		i++;
	}
	free_null(&file);
}

