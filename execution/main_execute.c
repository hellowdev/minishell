#include "../minishell.h"

char	**split_path(char *env)
{
	char	**p;
	int		i;

	i = 0;
	while (env[i] != '/')
		i++;
	p = ft_split(&env[i], ':');
	if (!p)
		return (NULL);
	return (p);
}

char	**wich_path(char **env)
{
	int		t;
	char	**mypath;

	t = 0;
	mypath = NULL;
	while (env[t])
	{
		if (ft_strnstr(env[t], "PATH", 5))
		{
			mypath = split_path(env[t]);
			if (!mypath)
				return (NULL);
			break ;
		}
		t++;
	}
	return (mypath);
}

char	*valid_path(char **env, char *cmd)
{
	char	**p;
	char	*path;
	int		i;

	i = 0;
	p = wich_path(env);
	if (!p)
		return (NULL);
	if (access(cmd, F_OK & X_OK) == 0)
		return (doubfree(p), ft_strdup(cmd));
	while (p[i])
	{
		path = ft_slash_join(p[i], cmd);
		if (!path)
			return (doubfree(p), NULL);
		if (access(path, F_OK & X_OK) == 0)
			return (doubfree(p), path);
		free(path);
		i++;
	}
	doubfree(p);
	return (NULL);
}

void	execute(t_parce *data, t_env *env, int *status)
{	
	
	if (data->next == NULL)
	{
		one_child(data, env);
		wait(status);
		*status = WEXITSTATUS(*status);
		return ;
	}
	else
	{
		first_child(data, env);
		wait(status);
		data = data->next;
	}
	listofchild(&data, env, status);
	last_child(data, env);
	wait(status);
	*status = WEXITSTATUS(*status);
	return ;
}
