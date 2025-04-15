#include "minishell.h"

extern char **environ;

int	check_words(char *s, t_token **head)
{
	int i;
	i = 0;
	if (ft_isspace(s[i]) == 0 && (s[i] != '<' && (s[i] != '<' \
		&& s[i + 1] != '<')) && (s[i] != '>' && (s[i] != '>' \
		&& s[i + 1] != '>')) && (s[i] != '|'))
			i += words(&s[i], &head);
	return (i);
}

int    main_parse(char *s)
{
	int i;
	t_token *head;
	int j;

	j = 0;
	i = 0;	
	while (s[i])
	{
		in_heredoc(&s[i], &head, &i, &j);
		if (j == -1)
			return (free(s), -1);
		// out_append(&s[i], &head, &i, &j);
		// if (j == -1)
		// 	return (free(s), -1);
		// handle_pipe(&s[i], &head, &i, &j); // handle syntax errors
		// if (j == -1)
		// 	return (free(s), -1);
		skip_space(&s[i], &i);
		i += check_words(&s[i], &head);
		i++;
	}
	return (i);
}

int main(int ac, char **env)
{
	(void )env;
	if (ac == 1)
	{
		char *line; 
		while ((line = readline("minishell$ ")))
		{
			add_history(line);
			if (main_parse(line) == -1)
				write(1, "must update exit status variable\n", 33);// UPDATE THE VALUE OF VARIABLE WITH 258
		}
	}
	
	
}














// if (s[i] == '<' || (s[i] == '<' && s[i + 1] == '<'))
// 			i += in_heredoc(&s[i], &head);
// 		else if (s[i] == '>' || (s[i] == '>' && s[i + 1] == '>'))
// 			i += out_append(&s[i], &head);
// 		else if (s[i] == '|')
// 			i += handle_pipe(&s[i], &head); // handle syntax errors
// 		else if (s[i] == 32)
// 			i += skip_space(&s[i]);
// 		if (ft_isspace(s[i]) == 0 || )
// 			i += words(&s[i], &head);
// 		i++;
// 	}