/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:12:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/18 19:31:16 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int strlen_herdoc(char *s)
{
	int i;

	i = 1;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (i);	
}

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
	ret = NULL;	
	ret = ft_strjoin(ft_strdup("/tmp/"), str);
	free(str);
	return (ret);
}

void	get_lineee(char *heredoc, int fd, bool quoted, t_expand *stock)
{
	char *line;

	line = NULL;
	while (1)
	{
		line = get_next_line(0);
		if (!line || ft_strcm_doc(line, heredoc) == 0)
			break ;
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

void	one_doc(t_parce *data, t_expand *stock)
{
	int		i_fork;

	i_fork = fork();
	if (i_fork == 0)
	{
		creat_file(data->heredoc, data->check_qt, 0, stock);
		exit(0);
	}
	wait(NULL);
}

void	first_doc(t_parce *data, t_expand *stock)
{
	int	i_fork;
	
	i_fork = fork();
	if (i_fork == 0)
	{
		creat_file(data->heredoc, data->check_qt, 0, stock);		
		exit(0);
	}
	wait(NULL);
}

int	listofdoc(t_parce **data, t_expand *stock)
{
	int i_fork;
	int i;

	i = 1;
	while ((*data)->next)
	{
		
		i_fork = fork();
		if (i_fork == 0)
		{
			creat_file((*data)->heredoc, (*data)->check_qt, i, stock);
			exit(0);
		}
		wait(NULL);
		i++;
		(*data) = (*data)->next;
	}
	return (i);
}

void	last_doc(t_parce *data, int *i, t_expand *stock)
{
	int i_fork;
	
	i_fork = fork();
	if (i_fork == 0)
	{	
		creat_file(data->heredoc, data->check_qt, *i, stock);	
		exit(0);
	}
	wait(NULL);
}

void	heredoc(t_parce *data, t_env *env, int status)
{
	int i;
	t_expand stock;

	stock.env = env;
	stock.status = status;
	if (data->next == NULL) // one NODE
		return (one_doc(data, &stock));
	else // FIRST NODE IN THE LIST
	{
		first_doc(data, &stock);
		data = data->next;
	}
	// THE LIST OF NODE SEPARATE BY PIPE
	i = listofdoc(&data, &stock);
	// THE LAST NODE
	last_doc(data, &i, &stock);
}
