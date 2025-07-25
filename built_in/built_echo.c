/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:05:28 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/04 16:57:00 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	double_len(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd || !*cmd)
		return (0);
	while (cmd[i])
		i++;
	return (i);
}

size_t	len_n(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '-' && cmd[1] == 110)
		i++;
	while (cmd[i] && cmd[0] == '-' && cmd[i] == 110)
		i++;
	return (i);
}

void	echo_cmd(char **cmd)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (cmd[i] && *cmd[i] && len_n(cmd[i]) == ft_strlen(cmd[i]))
	{
		j++;
		i++;
	}
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (double_len(cmd) > 2 && double_len(cmd) != i + 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (j > 0)
		return ;
	ft_putstr_fd("\n", 1);
	g_status = 0;
}
