#include "minishell.h"

int is_spcharc(char c)
{
	if ((c == '|' || c == '>'
	|| c == '&' || c == '(' || c == ')' 
	|| c == '#' || c == ';' || c == '<'))
		return (1);
	return (0);
}
void	skip_space(char *s, int *i)
{

	while (ft_isspace(s[*i]) == 1)
		(*i)++;
}


int	in_heredoc(char *s, t_token **head, int *j, int *i)
{
	
	if (s[*i] == '<' && s[*i + 1] != '<')
	{
		*j = red_infile(&s[*i], head);
		if (*j == -1)
		{
			return (-1);
		}
	}
	else if (s[*i] == '<' && s[*i + 1] == '<')
	{
		*j = here_doc(&s[*i], head);
		if (*j == -1)
		{
			return (-1);
		}
	}
	*i += *j;
	return (i);
}
int	double_qoute(char *s, t_token *new)
{
	int i;
	// char *p;
	i = 0;
	while (s && s[++i]) // 
	{
		if (s[i] == 34)
		{
			new->value = ft_strjoin(new->value, ft_substr(s, 0, i));
			// printf("[%s]\n", p);
			return (i);
		}
	}
	return (i);
}

int	words(char *s, t_token **head)
{
	int i;
	int j;
	j = 0;
	t_token *new = malloc(sizeof(t_token));
	i = 0;
	new->type = TOKEN_WORD;
	
	(void)head;
	if (is_spcharc(s[i]) == 1)
	{
		printf("error in words\n");
		// systax error
		// update $?
		return (0);
	}

	while (s && s[i] && s[i] != 32)
	{
		
		if (s[i] == 34)
		{
			new->value = ft_substr(s, 0, i);
			j = double_qoute(&s[i], new);
			i += j;
		}
		i++;
	}
	new->value = ft_strjoin(new->value, ft_substr(s, j, i));
	printf("[%s]\n", new->value);
	return (i);
}


