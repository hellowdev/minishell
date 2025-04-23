/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:36:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/04/23 18:35:49 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_parse(t_env *env, char *s)
{
	t_token *head;
	t_parce *list;
	list = NULL;
	head = NULL;
	tokenization(s, &head);
	pars_ing(&list, env, head);
}

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
			main_parse(env, line);
			free(line);
		}
	}
}
