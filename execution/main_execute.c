#include "../minishell.h"

void	execute(t_parce *data, t_env *env, int *status)
{	
	int pipefd[2];

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
	listofchild(&data, env, pipefd, status); // THE LIST OF NODE SEPARATE BY PIPE
	last_child(data, env, pipefd, status); // THE LAST NODE
	// close(pipefd[1]);
	// close(pipefd[0]);
	return ;
}
