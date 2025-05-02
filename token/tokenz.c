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

int	join_word(char *s, t_token **head)
{
	char *p;
	t_word	data;
	data.str = NULL;
	data.strsg = NULL;
	data.strdb = NULL;
	t_token *new;
	int i;

	i = 0;
	p = NULL;
	while (s[i] && !spec_char(s[i]))
	{
		i += check_chac(&s[i], &data);
		p = ft_strjoin(p, data.str);
		i += doub_qt(&s[i], &data);
		p = ft_strjoin(p, data.strdb);
		i += sing_qt(&s[i], &data);
		p = ft_strjoin(p, data.strsg);
	}
	new = ft_lstnew(p, WORD);
	ft_lstadd_back(head, new);
	return (i);
}

int	check_words(char *s, t_token **head)
{
	int i;

	i = 0;
	if (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>' && s[i] != '|')
			i += join_word(&s[i], head);
	return (i);
}