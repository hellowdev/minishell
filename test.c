#include <stdio.h>
#include <signal.h>
# include <readline/readline.h>  // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h> 
#include <unistd.h>
#include "minishell.h"

void    handle_sign(int sig)
{
    (void)sig;
    rl_replace_line();
    // write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

void    signals()
{
    signal(SIGINT, handle_sign);
	signal(SIGQUIT, SIG_IGN);
}
int main() {
    // Ignore SIGQUIT
    signals();
    while (1) {
    //    pause();
    }

    return 0;
}