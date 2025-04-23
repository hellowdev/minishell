#include "../minishell.h"

void    update_status(t_env *env)
{
    write(2, "syntax error near unexpected token\n", 36);
    while (env)
    {
        if (ft_strcmp(env->name_env, "status") == 1)
        {
            free(env->value_env);
            env->value_env = ft_strdup("258");
        }
        env = env->next;
    }
}
