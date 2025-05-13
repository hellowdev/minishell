/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:58:34 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/13 20:12:51 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_cmd(t_parce *data)
{
	char *path;
	
	if (data->cmd)
	{
		path = valid_path(environ, data->cmd[0]);
		if (!path)
			return (redire_err(data->cmd[0], ": command not found"), -1); // free here or free all in child?
		execve(path, data->cmd, environ);
		// printf("exec\n");
		// exit(0);
	}
	return (0);
}
