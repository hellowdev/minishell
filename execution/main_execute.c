#include "../minishell.h"

void	fd_closer(int fd, int *pipefd)
{
	close(fd);
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

int	i_child(t_parce *data, int tmp, int *pipefd, int check)
{
	// -------- INFILE --------- //
	if (dup_infile(data->infiles) == -1)
		return (fd_closer(tmp, pipefd), 1);
	else if (!data->infiles && check == 0) // if not infile and not the first one
		dup2(tmp, 0);
	// -------- OUTFILE --------- //
	if(dup_outfile(data->outfiles, data->append) == -1)
		return (fd_closer(tmp, pipefd), 1);
	else if (!data->outfiles && data->next) // if not outfile and next node 
		dup2(pipefd[1], 1);
	// -------- CMD --------- //
	fd_closer(tmp, pipefd);

	if (execute_cmd(data) == -1)
		return (127);
	
	return (0);
}


void	execute(t_parce *data, t_env *env, int *status)
{	
	int pipefd[2];
	int newfd;
	pipe(pipefd);
	if (data->next == NULL) // one NODE
	{
		one_child(data, env, pipefd, status);		
		return ;
	}
	else // FIRST NODE IN THE LIST
	{
		first_child(data, env, pipefd, status);
		data = data->next;
	}
	newfd = listofchild(&data, env, pipefd, status); // THE LIST OF NODE SEPARATE BY PIPE
	last_child(data, env, newfd, status); // THE LAST NODE
	return ;
}
