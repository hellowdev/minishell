#include "../minishell.h"

void    update_status(t_env *env)
{
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
