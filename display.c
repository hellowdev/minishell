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

// void	search_exp(char *str, int dol, t_env *env, int status)
// {
// 	int i;
// 	char *bfrdol = NULL;
// 	int j;
// 	char *name;
// 	char *value;
// 	if (dol) 
// 		bfrdol = ft_substr(str, 0, dol); 
// 	j = get_name(str);
// 	name = ft_substr(str, dol + 1, j - 1); // aftdol = HOME_3232$hi
// 	if (!ft_isalpha(str[j]) || !ft_isdigit(str[j]) || str[j] != '_')
// 		name = ft_substr(str, j, ft_strlen(str));
// 	while (env)
// 	{
// 		if (ft_strcmp(env->name_env, name)) // if env->name == HOME_3232 
// 		{
// 			value = ft_strdup(env->value_env); // value = /Users/ychedmi
// 			// str = ft_strjoin(bfrdol, value); // value = /Users/ychedmi +
// 		}
// 		env = env->next;
// 	}
	
// }
// void	disp_status(char **str, t_env *env, int status)
// {
// 	int i;
// 	int dol;
// 	// char *value;
// 	if (!str)
// 		return ;

// 	i = 0;
// 	while (str[i])
// 	{
		
// 		search_exp(str[i], env, status);
// 		i++;
// 	}
	
// }
