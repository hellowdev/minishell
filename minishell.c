/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:36:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/04/16 21:36:51 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main( int ac, char **av)
{
	char	*line;
	t_env	*env;

	(void )av;
	if (ac == 1)
	{
		copy_env(&env);
		while ((line = readline("minishell$ ")))
		{
			add_history(line);
			main_parse(line);
			free(line);
		}
	}
}
