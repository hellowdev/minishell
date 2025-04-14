#include "minishell.h"

extern char **environ;

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


