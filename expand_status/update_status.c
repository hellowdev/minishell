#include "../minishell.h"

void    update_status(int *status, char *s)
{
    write(2, "mini: syntax error near unexpected token `", 43);
    write(2, s, ft_strlen(s));
    write(2, "'\n", 2);
    *status = 258;
}
