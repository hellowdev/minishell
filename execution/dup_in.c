/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:37:17 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/19 11:33:37 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_infile(char **infile)
{
	int i;
	int cnt;
	int fd;

	i = 0;
	cnt = count_fd(infile);
	while (infile[i])
	{
		fd = open(infile[i], O_RDONLY);
		if (access(infile[i], F_OK) != 0)
			return (redire_err(infile[i], ": No such file or directory"));
		if (access(infile[i], R_OK) != 0)
			return (redire_err(infile[i], ": Permission denied"));
		if (fd < 0)
		{
			perror("minishell");
			write(2, "\n", 1);
			return (-1);
		}
		if (i < cnt) // close all fd - 1
			close(fd);
		i++;
	}
	return (fd);
}

int	dup_infile(char **infile, bool last_inf)
{
	int fd;

	if (infile)
	{
		fd = check_infile(infile);
		if (fd < 0)
			return (-1);
		if (last_inf == false)
			dup2(fd, 0);
		close(fd);
	}
	return (1);
}
