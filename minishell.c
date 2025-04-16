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

int	len_equal(char *s)
{
	int cnt;

	cnt = 0;
	while (s[cnt] && s[cnt] != '=')
		cnt++;
	return (cnt);
}

void	copy_env(t_env **head)
{
	int		i;
	t_env	*new;
	char	*name;
	char	*value;

	i = 0;
	while (environ[i])
	{
		name = ft_substr(environ[i], 0, len_equal(environ[i]));
		value = ft_substr(environ[i], len_equal(environ[i]) + 1, ft_strlen(environ[i]));
		new = lstnew_env(name, value);
		env_add_back(head, new);
		i++;
	}
	
}

void	display(t_env *list)
{
	while (list)
	{
		printf("%s=", list->name_env);
		printf("%s\n", list->value_env);
		list = list->next;
	}
	
}

void	disp_ar(char **str)
{
	int i = 0;
	while (str[i])
		printf("%s\n", str[i++]);
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
