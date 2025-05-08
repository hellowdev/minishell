#include "../minishell.h"

void    update_status(int *status)
{
    write(2, "syntax error near unexpected token\n", 36);
    *status = 258;
}
