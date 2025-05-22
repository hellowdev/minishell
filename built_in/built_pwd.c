/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:28:55 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/21 17:52:17 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_cmd(char **cmd)
{
	char	*ret;
	
	ret = getcwd(NULL, 0);
	if (!ret)
		return (redire_err(cmd[0], NULL), perror(" "));
	write(1, ret, ft_strlen(ret));
	write(1, "\n", 1);
}
