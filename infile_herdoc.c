#include "minishell.h"

int	red_infile(char *s, t_token **token)
{
	int i;

	i = 0;
	
	t_token *new;
	new->type = TOKEN_REDIRECT_IN;
	new = ft_lstnew(ft_strdup(s));
	ft_lstadd_back(token, new);
	// while (s[i] && s[i] !=)
	// {
	// 	if (is_spcharc(s[i]) == 0 && s[i] != 32) // <fe"
	// 		return (i);
	// 	else if (is_spcharc(s[i]) == 1)
	// 	{
	// 		printf("error in infile\n");
	// 		return(-1);
	// 		// systax error
	// 		// update exit status variable
	// 	}
	// 	i++;
	// }
	// return (i);
}

// int here_doc(char *s, t_token **token)
// {


// }