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
