/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:48:39 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/23 13:00:05 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	updt_oldpwd(t_env **env, char *cwd)
{
	t_env	*newenv;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp((tmp)->name_env, "OLDPWD") == 0)
		{
			free(tmp->value_env);
			tmp->value_env = cwd;
			return ;
		}
		tmp = tmp->next;
	}
	newenv = lstnew_env(ft_strdup("OLDPWD"), cwd);
	env_add_back(env, newenv);
}

void	updt_pwd(char *dir, t_env **env)
{
	t_env *newhead;
	
	newhead = (*env);
	while (newhead)
	{
		if (ft_strcmp(newhead->name_env, "PWD") == 0)
		{	
			free(newhead->value_env);
			newhead->value_env = dir;
			return ;
		}
		newhead = newhead->next;
	}
}

void	cd_cmd(char **cmd, t_env **env)
{
	char	*ret;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cmd[1])
	{
		if (chdir(cmd[1]) == 0) // change directory
			updt_oldpwd(env, cwd);
		else
			return (redire_err(cmd[1], NULL), perror(" "));
		ret = getcwd(NULL, 0); // actual directory 
		updt_pwd(ret, env);
	} // change dir
	else if (!cmd[1])
	{
		ret = env_searsh(*env, "HOME");
		if (!ret)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2));
		updt_oldpwd(env, cwd);
		updt_pwd(ft_strdup(ret), env);
		if (chdir(ret) < 0)
			return (redire_err(ret, NULL), perror(" "));
	}
	
}
