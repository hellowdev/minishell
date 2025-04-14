#include "../minishell.h"

bool    ft_qoute(char *s)
{
    int i;
    i = 0;
    while (s[i])
    {
        if (s[i] == '"')
            return true;
        i++;
    }
    return false;
}
void    test(char *s)
{
    int i = 0;
    int cnt;
    cnt = 0;
    while (s[i])
    {
        if (s[i] == '"')
        {
            while (s[i] != '"')
                i++;
        }
        if (ft_isspace(s[i]) == 0 && (ft_isspace(s[i + 1]) == 1 || ft_isspace(s[i + 1]) == '\0') || )
            cnt++;
        i++;
    }
    
}