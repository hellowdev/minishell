/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:33:37 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/26 20:16:44 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	handle_signals(int sig)
{
	(void)sig;
    // printf("hel");
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
    
}
void	handle_child(int sig)
{
        //  printf("in child SIG");

	if (sig == 2)
    {
        printf("in child SIG");
        signal(SIGINT, SIG_IGN);
        exit(1);
    }
}





