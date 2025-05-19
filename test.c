#include "minishell.h"

void    signalHandler(int x)
{
    printf("signal > %d\n", x);
    exit(2);
}

int main()
{
    signal(SIGINT, SIG_IGN);  
    while (1)
    {
        printf("cc\n");
    }
    
    
}