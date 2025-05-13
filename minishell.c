/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:36:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/13 20:32:46 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_word(char *s, int *status)
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
			return (update_status(status, "&, (, ), #, ;"), -1);
		i++;
	}
    return (1);
}

int calc_qout(char *s, int *status)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			i += double_qt(&s[i]);
			if (!s[i])// s[i] = '\0'
				return (update_status(status, "\""), -1);
		}
		else if (s[i] == 39)
		{
			i += single_qt(&s[i]);
			if (!s[i])
				return (update_status(status, "'"), -1);
		}
		i++;
	}
	return (1);
}

t_parce	*main_parse(int *status, char *s, t_env *env)
{
	t_token *head;
	t_parce *list;

	list = NULL;
	head = NULL;
	if (calc_qout(s, status) == -1 || valid_word(s, status) == -1)
		return (NULL);
	tokenization(s, &head); //
	if (!head)
		return (NULL);
	pars_ing(&list, status, head, env);
	ft_lstclear(head);
	if (list)
		execute(list, env, status);
	
	return (list);
}

int main(int ac, char **av)
{
	char	*line;
	t_env	*env;
	int		status;
	t_parce *lst;

	status = 0;
	env = NULL;
	(void )av;
	if (ac == 1)
	{
		copy_env(&env);
		while ((line = readline("minishell$ ")))
		{
			add_history(line);
			lst = main_parse(&status, line, env);
			// execute(lst, env, &status);
			free(line); //
		}
	}
	system("leaks -q minishell");
}
