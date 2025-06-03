/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:57:44 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 18:30:32 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fd_er(int fd)
{
	if (fd < 0)
	{
		perror("minishell");
		write(2, "\n", 1);
		return (-1);
	}
	return (fd);
}

int	check_dire(char *file)
{
	struct stat	info;

	if (stat(file, &info) != 0)
		return (redire_err(file, ": No such file or directory"), 0);
	if (S_ISDIR(info.st_mode))
		return (redire_err(file, ": is a directory"), 0);
	if (access(file, W_OK) != 0)
		return (redire_err(file, ": Permission denied"), 0);
	return (1);
}

int	check_outfile(char **outfile, bool *append)
{
	int	i;
	int	fd;

	i = 0;
	while (outfile[i])
	{
		fd = open(outfile[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (append[i] == false)
		{
			close(fd);
			fd = open(outfile[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		if (check_dire(outfile[i]) == 0)
			return (-1);
		if (fd_er(fd) == -1)
			return (-1);
		if (i < count_fd(outfile))
			close(fd);
		i++;
	}
	return (fd);
}

int	dup_outfile(char **outfile, bool *append)
{
	int	fd;

	if (outfile)
	{
		fd = check_outfile(outfile, append);
		if (fd < 0)
			return (g_status = 1, (-1));
		dup2(fd, 1);
		close(fd);
	}
	return (1);
}
