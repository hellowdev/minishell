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

int	doub_quote(char *s)
{
	int i;

	i = 1; // i = 0 ??
	while (s[i] && s[i] != 34)
	{
		i++;
	}
	return (i);
}

int	sing_quote(char *s)
{
	int i;

	i = 1; // i = 0 ??
	while (s[i] && s[i] != 39)
		i++;
	return (i);
}


int	ft_lenspace(char *s)
{
	int i;

	i = 0;
	while (s[i] && ft_isspace(s[i]) == 0 \
	&& s[i] != '<' && s[i] != '>' && s[i] != '|')
	{
		if (s[i] == 34)
			i += doub_quote(&s[i]);
		else if (s[i] == 39)
			i += sing_quote(&s[i]);
		i++;
	}
	return (i);
}
int words(char *s, t_token **token)
{
	t_token *new;
	int ret;
	
	ret = ft_lenspace(s);
	new = ft_lstnew(ft_substr(s, 0, ret), WORD);
	ft_lstadd_back(token, new);
	return (ret); 
}

int	check_words(char *s, t_token **head)
{
	int i;
	i = 0;

	if (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>' && s[i] != '|')
			i += words(&s[i], head);
	return (i);
}

