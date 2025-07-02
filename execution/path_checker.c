/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:01:10 by ychedmi           #+#    #+#             */
/*   Updated: 2025/07/02 20:04:09 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*slash_path(char *cmd)
{
	struct stat	info;

	if (is_slash(cmd) && stat(cmd, &info) != 0)
		return (g_status = 127, \
		redire_err(cmd, ": No such file or directory"), NULL);
	if (S_ISDIR(info.st_mode))
		return (g_status = 126, redire_err(cmd, ": is a directory"), NULL);
	if (is_slash(cmd) && access(cmd, X_OK) != 0)
		return (g_status = 126, redire_err(cmd, ": Permission denied"), NULL);
	return (ft_strdup(cmd));
}

char	*only_cmd(t_env *env, char *cmd)
{
	char	**env_path;
	char	*joined_path;
	int		i;

	i = 0;
	env_path = get_path(env);
	if (!env_path || !*env_path)
		return (g_status = 127, \
		redire_err(cmd, ": No such file or directory"), NULL);
	while (env_path[i])
	{
		joined_path = ft_slash_join(env_path[i], cmd);
		if (access(joined_path, F_OK) == 0)
		{
			if (access(joined_path, X_OK) == 0)
				return (doubfree(env_path), joined_path);
			else
				return (doubfree(env_path), free_null(&joined_path), \
				g_status = 126, redire_err(cmd, ": Permission denied"), NULL);
		}
		free_null(&joined_path);
		i++;
	}
	return (doubfree(env_path), g_status = 127, \
	redire_err(cmd, ": command not found"), NULL);
}

char	*path(t_env *env, char *cmd)
{
	if (!*cmd)
		return (g_status = 127, \
		redire_err(cmd, ": command not found"), NULL);
	if (is_slash(cmd))
		return (slash_path(cmd));
	return (only_cmd(env, cmd));
}
