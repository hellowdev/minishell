#include "../minishell.h"


char	**get_path(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
		{
			paths = ft_split(env[i] + 5, ':');
			if (!paths)
				return (NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

void    f_child(t_parce *list, t_env *env)
{
    char **path;
    int infd;

    path = get_path(environ);
    if (list->cmd)
        get_cmnd(list->cmd[0], path);
    if (list->infiles)
        infd = get_in_fd(list->infiles);
    if (list->outfiles)
        // out_fd =
        // if (list->append)
    if (list->heredoc)
}

void    execute(t_parce *list, t_env *env, int *status)
{
	(void)env;
	if (!list)
		return ;
	
    int fds[2];
    int retfork;
    if (list->next == NULL)
    {
        retfork = fork();
        if (retfork == 0)
		{
            f_child(list, env); // first node without next
			// printf("first\n");
			// exit(13);
		}
        wait(status);
		*status = WEXITSTATUS(*status); // WEXITSTATUS convert the value recepted with wait to int
		// printf("status > %d\n", *status);
		return ;
    }
    else
    {
        pipe(fds);
        retfork = fork();
        if (retfork == 0)
		{
            f_child(fds, env); // first node with next
			// printf("first in list\n");
			exit(1);
		}
        wait(status);
        list = list->next;
    }
    while (list->next)
    {
        retfork = fork();
        if (retfork == 0)
		{
            child(fds);
			// printf("list\n");
			// exit(0);
		}
        wait(status);
        list = list->next;
    }
    retfork = fork();
    if (retfork == 0)
	{
        last_child(); // last node
		// printf("last\n");
		// exit(123);
	}
    wait(status);
}