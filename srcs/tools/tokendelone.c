#include "../../minishell.h"

void	tokendelone(t_token *lst)
{
	if (lst)
	{
		ft_free(lst->content);
		free(lst);
	}
}