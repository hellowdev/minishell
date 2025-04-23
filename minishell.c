/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:36:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/04/23 22:48:36 by ychedmi          ###   ########.fr       */
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
	
	while (list)
	{
		printf("--cmd--\n");
		if (list->cmd)
			disp_ar(list->cmd);
		printf("--heredoc--\n");
		if (list->heredoc)
			disp_ar(list->heredoc);
		printf("--infile--\n");
		if (list->infiles)
			disp_ar(list->infiles);
		printf("--outfile--\n");
		if (list->outfiles)
			disp_ar(list->outfiles);
		printf("--   [pipe]  --\n");
		list = list->next;
	}
	
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
