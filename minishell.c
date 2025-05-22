/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:36:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/22 16:23:31 by ychedmi          ###   ########.fr       */
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
	tokenization(s, &head);
	if (!head)
		return (NULL);
	pars_ing(&list, status, head, env);
	ft_lstclear(head);
	return (list);
}
// void	signalHandler(int x)
// {
// 	if (x == 2)
// 		write(1, "\nminishell$ ", 12);
// }

int main(int ac, char **av)
{
	char	*line;
	t_env	*env;
	int		status;
	t_parce *lst;

	status = 0;
	env = NULL;
	(void )av;
	// signal(SIGQUIT, SIG_IGN);
	if (ac == 1)
	{
		copy_env(&env);
		while ((line = readline("minishell$ ")))
		{
			if (ft_strcmp(line, "exit") == 0)
				return (free(line), free_env(env), free_doublst(&lst), status); // free line tparce 
			add_history(line);
			lst = main_parse(&status, line, env);
			if (lst)
				execute(lst, &env, &status);
			free(line);
		}
	}
}
 