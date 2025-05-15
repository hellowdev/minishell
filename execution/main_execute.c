#include "../minishell.h"


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
	int newfd;
	t_child	pack;
	pipe(pack.pipefd);
	pack.env = env;
	pack.status = status;
	if (data->next == NULL) // one NODE
		return (one_child(data, env, pack.pipefd, status));
	else // FIRST NODE IN THE LIST
	{
		pack.ids = malloc(ft_lstsize(data) * sizeof(int));
		first_child(data, &pack);
		data = data->next;
	}
	newfd = listofchild(&data, &pack); // THE LIST OF NODE SEPARATE BY PIPE
	last_child(data, newfd, &pack); // THE LAST NODE
	wait_proc(&pack);
	return ;
}
