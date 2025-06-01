#include "../minishell.h"

char	**ft_doubjoin(char **tab1, char **tab2)
{
	char	**p;
	int		i;
	int		v;

	p = malloc((double_len(tab1) + double_len(tab2) + 1) * sizeof(char *));
	i = 0;
	while (tab1[i])
	{
		p[i] = ft_strdup(tab1[i]);
		i++;
	}
	v = 0;
	while (tab2[v])
		p[i++] = ft_strdup(tab2[v++]);
	p[i] = NULL;
	doubfree(tab1);
	return (p);
}
