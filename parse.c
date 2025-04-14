#include "minishell.h"

int is_spcharc(char c)
{
	if ((c == '|' || c == '>'
	|| c == '&' || c == '(' || c == ')' 
	|| c == '#' || c == ';' || c == '<'))
		return (1);
	return (0);
}
int	red_infile(char *s)
{
	int i;

	i = 1;
	if (s[0] != '<')
		return (0);
	while (s && s[i])
	{
		if (is_spcharc(s[i]) == 0 && s[i] != 32)
			return (i);
		else if (is_spcharc(s[i]) == 1)
		{
			printf("error in infile\n");
			return(-10);
			// systax error
		}
		i++;
	}
	return (i);
}
int	double_qoute(char *s, t_token *new)
{
	int i;
	// char *p;
	i = 0;
	while (s && s[++i])
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
		return (-10);
		// systax error
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

int    main_parse(char *s)
{
	int i;
	int j;
	t_token *head;
	
	i = 0;
	j = 0;
	while (s[i])
	{
		j = red_infile(&s[i]);
		if (j == -10)
			return (-1);
		i += j;
		
		i += words(&s[i], &head);
		// red_outfile(&s[i]);
		i++;
	}
	return 1;
}


