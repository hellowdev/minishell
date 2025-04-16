#include "minishell.h"

void	display_env(t_env *list)
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
