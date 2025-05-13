/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:57:44 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/13 20:12:48 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_outfile(char **outfile, bool *append)
{
	int i;
	int fd;

	i = 0;
	while (outfile[i])
	{
		fd = open(outfile[i], O_CREAT | O_WRONLY, 0644); // change here was RDONLY
		if (append[i] == false)
			fd = open(outfile[i], O_CREAT | O_WRONLY | O_TRUNC, 0644); // change here was RDONLY
		if (access(outfile[i], W_OK) != 0)
			return (redire_err(outfile[i], ": Permission denied"));
		if (fd < 0)
		{
			perror("minishell");
			write(2, "\n", 1);
			return (-1);
		}
		if (i < count_fd(outfile)) // close all fd - 1
			close(fd);
		i++;
	}
	return (fd);
}

int	dup_outfile(char **outfile, bool *append)
{
	int fd;

	if (outfile)
	{
		fd = check_outfile(outfile, append);
		if (fd < 0)
			return (-1);
		printf("outfile\n");
		dup2(fd, 1);
		close(fd);
	}
	return (1);
}
