#include "minishell.h"

int ft_size(t_env *lst)
{
    int i;
    i = 0;
    if(!lst)
        return 0;
    while (lst)
    {
        i++;
        lst = lst->next;
    }
    return (i);
}
char	**double_env(t_env *env)
{
	char **ret;
    char *str;
	int i;

	i = 0;
	ret = malloc((ft_size(env) + 1) * sizeof(char *));
	while (env)
	{
		ret[i] = ft_strjoin(env->name_env, ft_strdup("="));
		ret[i] = ft_strjoin(ret[i], env->value_env);
        printf("%s\n", ret[i]);
		env = env->next;
		i++;
	}
    printf("-------------------------------\n");
	ret[i] = NULL;
	return (ret);
}

int main()
{
    char **ret;
    t_env *env;
    env = NULL;
    copy_env(&env);
    ret = double_env(env);
    disp_ar(ret);
}