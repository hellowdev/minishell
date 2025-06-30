/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:28:55 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/29 21:30:10 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_cmd(char **cmd)
{
	char	*ret;

	g_status = 0;
	ret = getcwd(NULL, 0);
	if (!ret)
		return (redire_err(cmd[0], NULL), perror(" "));
	write(1, ret, ft_strlen(ret));
	write(1, "\n", 1);
	free_null(&ret);
}
