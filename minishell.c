/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:36:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/08 16:15:33 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_word(char *s)
{
	int i;
	i = 0;
	
	while (s[i])
	{
		if (s[i] == 34)
			i += double_qt(&s[i]);
		else if (s[i] == 39)
			i += single_qt(&s[i]);
		if (is_spcharc(s[i]) != 0)
			return (-1);
		i++;
	}
    return (1);
}

int calc_qout(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			i += double_qt(&s[i]);
			if (!s[i])
				return (-1);
		}
		else if (s[i] == 39)
		{
			i += single_qt(&s[i]);
			if (!s[i])
				return (-1);
		}
		i++;
	}
	return (1);
}

void	main_parse(int *status, char *s, t_env *env)
{
	t_token *head;
	t_parce *list;

	list = NULL;
	head = NULL;
	if (calc_qout(s) == -1 || valid_word(s) == -1)
		return (update_status(status));
	tokenization(s, &head); //
	if (!head)
		return ;
	pars_ing(&list, status, head, env);
	
	// expand_status(list, s);
	ft_lstclear(head);
	
}

int main(int ac, char **av)
{
	char	*line;
	t_env	*env;
	int		status;

	status = 0;
	env = NULL;
	(void )av;
	if (ac == 1)
	{
		copy_env(&env);
		
		// pause();
		while ((line = readline("minishell$ ")))
		{
			add_history(line);
			main_parse(&status, line, env);
			// printf("stt: %d\n", status);
			free(line); //
		}
	}
	system("leaks -q minishell");
}
