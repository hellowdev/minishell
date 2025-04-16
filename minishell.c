#include "minishell.h"

extern char **environ;

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

void	main_parse(char *s)
{
	t_token *head;

	head = NULL;
	tokenization(s, &head);
}



int main( int ac, char **av)
{
	char	*line;
	t_env	*env;

	(void )av;
	if (ac == 1)
	{
		copy_env(&env);
		while ((line = readline("minishell$ ")))
		{
			add_history(line);
			main_parse(line);
			free(line);
		}
	}
	
	
}
