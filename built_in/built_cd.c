/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:48:39 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 13:06:36 by ychedmi          ###   ########.fr       */
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

void	cd_option(t_env **env, char *cwd)
{
	char *ret;

	ret = env_searsh(*env, "OLDPWD");
	if (!ret)
		return (status = 1, ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2));
	updt_oldpwd(env, cwd);
	updt_pwd(ft_strdup(ret), env);
	if (chdir(ret) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(ret, 2);
		perror(" ");
		return (status = 1, free_null(&ret));
	}
	printf("%s\n", ret);
}

void	cd_param(char **cmd, t_env **env, char *cwd)
{
	char	*ret;

	if (cmd[1] && *cmd[1])
	{
		if (ft_strcmp(cmd[1], "-") == 0)
			return (cd_option(env, cwd));
		if (chdir(cmd[1]) == 0)
			updt_oldpwd(env, cwd);
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(cmd[1], 2);
			return (status = 1, perror(" "), free_null(&cwd));
		}
		ret = getcwd(NULL, 0);
		updt_pwd(ret, env);
	}
}

void	cd_cmd(char **cmd, t_env **env)
{
	char	*ret;
	char	*cwd;

	status = 0;
	cwd = getcwd(NULL, 0);
	cd_param(cmd, env, cwd);
	if (!cmd[1])
	{
		ret = env_searsh(*env, "HOME");
		if (!ret)
			return (status = 1, ft_putstr_fd("minishell: cd: HOME not set\n", 2));
		updt_oldpwd(env, cwd);
		updt_pwd(ret, env);
		if (chdir(ret) < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("cd: ", 2);
			return (status = 1, ft_putstr_fd(ret, 2), perror(" "));
		}
	}
}
