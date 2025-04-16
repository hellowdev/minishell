#include "minishell.h"

int	doub_qt(char *s)
{
	int i;

	i = 1; // i = 0 ??
	while (s[i] && s[i] != 34)
	{
		i++;
	}
	return (i);
}


int	sing_qt(char *s)
{
	int i;

	i = 1; // i = 0 ??
	while (s[i] && s[i] != 39)
		i++;
	return (i);
}

int	check_words(char *s, t_token **head)
{
	int i;
	i = 0;
	if (s[i] && ft_isspace(s[i]) == 0 && (s[i] != '<' && (s[i] != '<' \
		&& s[i + 1] != '<')) && (s[i] != '>' && (s[i] != '>' \
		&& s[i + 1] != '>')) && (s[i] != '|'))
			i += words(&s[i], head);
	return (i);
}

int	ft_lenspace(char *s)
{
	int i;
	i = 0;
	
	while (s[i] && ft_isspace(s[i]) == 0 \
	&& s[i] != '<' && s[i] != '>'  && s[i] != '|')
	{
		if (s[i] == 34)
			i += doub_qt(&s[i]); // i += len_qt(&s[i + 1]); ???
		else if (s[i] == 39)
			i += sing_qt(&s[i]);
		i++;
	}
	return (i);
}
int words(char *s, t_token **token)
{
	t_token *new;
	int ret;
	ret = ft_lenspace(s);
	new = ft_lstnew(ft_substr(s, 0, ret));
	new->type = TOKEN_WORD;
	// printf("word: [%s]\n", new->value);
	ft_lstadd_back(token, new);
	return (ret); 
}
