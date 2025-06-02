/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:36:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 00:32:35 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status = 0;

void	disable_ctrl_echo(void)
{
	struct termios		tty;

	tcgetattr(STDIN_FILENO, &tty);
	tty.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

t_parce	*main_parse(char *s, t_env *env)
{
	t_token	*head;
	t_parce	*list;

	list = NULL;
	head = NULL;
	if (calc_qout(s) == -1 || valid_word(s) == -1)
		return (NULL);
	tokenization(s, &head);
	if (!head)
		return (NULL);
	pars_ing(&list, head, env);
	ft_lstclear(head);
	return (list);
}

int	int_while(t_env **env)
{
	char	*line;
	t_parce	*lst;

	lst = NULL;
	while (1)
	{
		signalss(&status);
		line = readline("minishell$ ");
		if (!line)
			return (free_env(*env), *env = NULL, \
			free_doublst(&lst), printf("exit\n"), 0);
		if (ft_strcmp(line, "exit") == 0)
			return (free(line), free_env(*env), *env = NULL, \
			free_doublst(&lst), printf("exit\n"), status);
		if (*line)
			add_history(line);
		lst = main_parse(line, *env);
		free_null(&line);
		if (lst)
			execute(lst, env);
		free_doublst(&lst);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_env	*env;
	int		ret;

	(void)av;
	ret = 0;
	env = NULL;
	disable_ctrl_echo();
	if (ac == 1)
	{
		copy_env(&env);
		ret = int_while(&env);
		free_env(env);
	}
	return (ret);
}
