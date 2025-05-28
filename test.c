#include "minishell.h"

void	handle_signals(int sig)
{
	(void)sig;

	write(1, "\n", 1);
    
	printf("in parent >\n");
}
int main()
{
    int status = 0;

    signal(SIGINT, handle_signals);

    char **f = malloc(2 * sizeof(char *));
    f[0] = "cat";
    f[1] = NULL;
    int  i_fork = fork();
	if (i_fork == 0)
	{
        signal(SIGINT, handle_signals);
        execve("/bin/cat", f, environ);
	}
    wait(&status);

	if (WIFSIGNALED(status))
	{
		printf("signal value %d\n", WTERMSIG(status));
		printf("SIG > %d\n", WIFSIGNALED(status));
	}
	
}