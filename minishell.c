/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:36:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/26 20:38:44 by ychedmi          ###   ########.fr       */
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
//     (void)x;
	
// }
// void	f()
// {
// 	system("leaks -q minishell");
// }
// int	check_eof(char *input)
// {
// 	int i = 0;
// 	if (input[i] == EOF)
// 		return 1;
	
// }

int main(int ac, char **av)
{
	char	*line;
	t_env	*env;
	int		status;
	t_parce *lst;

	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	status = 0;
	env = NULL;
	(void)av;
	if (ac == 1)
	{
		copy_env(&env);
		while (1)
		{
			line = readline("minishell$ \0");
			if (!line)
			{
				printf("exit\n");
				exit(0);
			}
			if (ft_strcmp(line, "exit") == 0)
				return (free(line), free_env(env), free_doublst(&lst), status); // free line tparce
			add_history(line);
			lst = main_parse(&status, line, env);
			if (lst)
				execute(lst, &env, &status);
			free_doublst(&lst);
			free_null(&line);
		}
		free_env(env);
	}
}
 