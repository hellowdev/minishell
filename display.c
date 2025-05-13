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
	if (!str)
		return ;
	int i = 0;
	while (str[i])
		printf("%s\n", str[i++]);
}


int	find_dollar(char *s)
{
	int i;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (0);
}
int	get_name(char *s)
{
	int i;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' || !ft_isdigit(s[i]) || !ft_isalpha(s[i]) || s[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

