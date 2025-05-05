#include "../minishell.h"

void	tokenization(char *s, t_token **head)
{
	int i;
	int j;

	j = 0;
	i = 0;	
	while (s[i])
	{
		i += infile_heredoc(&s[i], head);
		i += outfile_append(&s[i], head);
		i += handle_pipe(&s[i], head);
		i += check_words(&s[i], head);
		if (ft_isspace(s[i]) == 1)
			i++;
	}
}
int spec_char(char c)
{
	if (!ft_isspace(c) && c != '<' && c != '>' && c != '|')
		return (0);
	return (1);
}

int	join_word(char *s, t_word *data)
{
	char *str;

	str = NULL;
	while (s[data->i] && !spec_char(s[data->i]))
	{
		data->i += check_chac(&s[data->i], &str);
		data->p = ft_strjoin(data->p, str);
		free_null(&str);
		data->i += doub_qt(&s[data->i], &str);
		data->p = ft_strjoin(data->p, str);
		free_null(&str);
		data->i += sing_qt(&s[data->i], &str);
		data->p = ft_strjoin(data->p, str);
		free_null(&str);
	}
	return (data->i);
}

int	check_words(char *s, t_token **head)
{
	int i;
	t_word data;
	t_token *new;
	data.p = NULL;
	data.i = 0;
	i = 0;
	if (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>' && s[i] != '|')
			i += join_word(&s[i], &data);
	if (data.p)
	{
		new = ft_lstnew(data.p, WORD);
		ft_lstadd_back(head, new);
	}
	return (i);
}
