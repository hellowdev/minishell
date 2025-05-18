/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:41:19 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/18 18:44:27 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int strlen_herdoc(char *s)
// {
// 	int i;

// 	i = 1;
// 	while (s[i])
// 	{
// 		if (s[i] == '$')
// 			return (i);
// 		i++;
// 	}
// 	return (i);	
// }

// int	doc_word(char *s, char **value)
// {
// 	int i;
// 	int len;
// 	char *word;

// 	i = 0;
// 	len = 0;
// 	if (s[i] != '$')
// 	{
// 		len = strlen_herdoc(&s[i]);
// 		word = ft_substr(s ,i ,len);
// 		*value = ft_strjoin(*value, word);
// 		free_null(&word);
// 	}
// 	return (len);
// }

// char	*expand_doc(char *str, t_env *env, int status)
// {
// 	int j;
// 	char *value;

// 	value = NULL;
// 	j = 0;
// 	while (str[j])
// 	{
		
// 		j += not_exp(&str[j], &value);
// 		j += expand(&str[j], &value, env, status);
// 		j += doc_word(&str[j], &value);
// 		if (str[j] == '$' && (str[j + 1] == '$' || !str[j + 1]))
// 		{
// 			value = ft_strjoin(value, "$");
// 			j++;
// 		}
// 	}
// 	free_null(&str);
// 	return (value);
// }

// void	get_line(char *heredoc, int fd, bool quoted, t_child *pack)
// {
// 	char *line;
	
// 	line = NULL;
// 	while (1)
// 	{
// 		line = get_next_line(0);
// 		if (!line || ft_strcm_doc(line, heredoc) == 0)
// 			break ;
// 		if (!quoted)
// 			line = expand_doc(line, pack->env, *pack->status);
// 		write(fd, line, ft_strlen(line));
// 		free_null(&line);
// 	}	
// 	return ;
// }

// int	check_heredoc(char **heredoc, bool quoted, t_child *pack)
// {
// 	int	i;
// 	int	fd;

// 	i = 0;
// 	while (heredoc[i])
// 	{
// 		fd = open("/tmp/tmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
// 		if (access("/tmp/tmp", R_OK & W_OK) != 0)
// 			return (redire_err("tmp", ": Permission denied"));
// 		get_line(heredoc[i], fd, quoted, pack);
// 		close(fd);
// 		i++;
// 	}
// 	fd = open("/tmp/tmp", O_RDWR, 0777);
// 	return (fd);
// }

int	dup_heredoc(char **heredoc, bool input, int index)
{
	int		fd;
	char	*file;
	
	file = NULL;
	if (heredoc && input == true)
	{
		file = file_name(index);
		fd = open(file, O_RDONLY, 0644);
		if (fd < 0)
			return (-1);
		dup2(fd, 0);
		close(fd);
		free_null(&file);
	}
	return (1);
}
