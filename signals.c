/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:33:37 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/28 17:55:54 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_doc_sig(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(0);
}
void	handle_signals(int sig)
{
	(void)sig;

	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	// printf("in parent >\n");
}

void	signalss()
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
}






