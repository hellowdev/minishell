#include "minishell.h"

// int	double_qoute(char *s, t_token *new)
// {
// 	int i;
// 	i = 0;
// 	while (s && s[++i])
// 	{
// 		if (s[i] == 34)
// 		{
// 			new->value = ft_strjoin(new->value, ft_substr(s, 0, i + 1));
// 			printf("check here >> [%s]\n", new->value);
// 			return (i);
// 		}
// 	}
// 	return (i);
// }

int	len_qt(char *s)
{
	int i;

	i = 1; // i = 0 ??
	while (s[i] && s[i] != 34)
	{
		i++;
	}
	return (i);
}

int	ft_lenspace(char *s)
{
	int i;
	i = 0;
	
	while (s[i] && ft_isspace(s[i]) == 0)
	{
		if (s[i] == 34)
			i += len_qt(&s[i]); // i += len_qt(&s[i + 1]); ???
		i++;
	}
	return (i);
}
int words(char *s, t_token **token)
{
	t_token *new;
	int ret;
	ret = ft_lenspace(s);
	new = ft_lstnew(ft_substr(s, 0, ret));
	new->type = TOKEN_WORD;
	printf("[%s]\n", new->value);
	ft_lstadd_back(token, new);
	return (ret); 
}
