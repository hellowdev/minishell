/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:41:19 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/28 21:37:42 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	dup_heredoc(char **heredoc, bool input, int index)
{
	int		fd;
	char	*file;
	
	file = NULL;
	if (heredoc && input == true)
	{
		file = file_name(index);
		fd = open(file, O_RDONLY, 0644);
		if (fd < 0)
			return (-1);
		dup2(fd, 0);
		close(fd);
		free_null(&file);
	}
	return (1);
}
