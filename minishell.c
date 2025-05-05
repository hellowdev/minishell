/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:36:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/05 10:51:45 by ychedmi          ###   ########.fr       */
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
	if (!head)
		return ;
	pars_ing(&list, env, head);
	
	ft_lstclear(head);
	
}

int main(int ac, char **av)
{
	char	*line;
	t_env	*env;
	env = NULL;
	(void )av;
	if (ac == 1)
	{
		copy_env(&env);
		while ((line = readline("minishell$ ")))
		{
			add_history(line);
			main_parse(env, line);
			// "$VAR" --> not splited and $VAR --> split with space 
			// handle || syntax err
			free(line); //
		}
	}
	system("leaks -q minishell");
}
