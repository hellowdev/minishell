/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:31:44 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/04 13:53:49 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	if_notnum(int check, t_parce *data, char *cmd, t_env **env)
{
	if (if_num(cmd) == 0 || check == -1)
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" : numeric argument required\n", 2);
		free_doublst(&data);
		free_env(*env);
		exit(255);
	}
}

void	exit_cmd(t_parce *data, char **cmd, t_env **env)
{
	int	nb;
	int	check;

	check = 0;
	if (!cmd[1])
	{
		printf("exit\n");
		free_doublst(&data);
		free_env(*env);
		exit(g_status);
	}
	nb = ft_atoi(cmd[1], &check);
	if_notnum(check, data, cmd[1], env);
	if (cmd[2])
		return (g_status = 1, \
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2));
	printf("exit\n");
	free_doublst(&data);
	free_env(*env);
	exit(nb);
}
