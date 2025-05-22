/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:05:28 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/22 11:40:12 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	double_len(char **cmd)
{
	int i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
		i++;
	return (i);
}

void	echo_cmd(char **cmd)
{
	int i;

	i = 1;
	if (cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
		i = 2;
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (double_len(cmd) > 2 && double_len(cmd) != i + 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
		return ;
	ft_putstr_fd("\n", 1);
}
