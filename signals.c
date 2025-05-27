/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:33:37 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/27 20:14:12 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int sig)
{
	(void)sig;

	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	// printf("in parent > %d\n", signalss);
}

void	signalss(t_env *env)
{
	int lvl;
	char *value;
	
	value = env_searsh(env, "@#.@123");
	lvl = ft_atoi(value);
	free_null(&value);
	if (lvl == 0)
		signal(SIGINT, handle_signals);
	else
	{
		signal(SIGINT, SIG_IGN);
	}
	signal(SIGQUIT, SIG_IGN);
}






