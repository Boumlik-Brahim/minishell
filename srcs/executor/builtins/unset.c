/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:22:34 by bbrahim           #+#    #+#             */
/*   Updated: 2022/06/29 18:23:46 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_delete_env(t_env	*current, t_env	*next)
{
	current->next = next->next;
	if (next->key)
		free(next->key);
	if (next->value)
		free(next->value);
	free(next);
}

/* -------------------------------------------------------------------------- */

void	ft_unset_env(t_env *env, char *data)
{
	t_env	*current;	

	current = env;
	while (current)
	{
		if (current->next != NULL)
		{
			if (ft_strcmp(current->next->key, data) == 0)
			{
				ft_delete_env(current, current->next);
				return ;
			}
		}
		current = current->next;
	}
}

/* -------------------------------------------------------------------------- */

int	ft_chk_unset(char	*data)
{
	int	i;

	i = -1;
	while (data[++i])
	{
		if (!ft_isalpha(data[i]) && data[i] != '_')
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */

int	ft_unset(t_env *env, char **data)
{
	int	i;

	i = 0;
	while (data[++i])
	{
		if (data[i][0] == '_' && data[i][1] == '\0')
			return (EXIT_FAILURE);
		if (ft_chk_unset(data[i]) == EXIT_SUCCESS)
			ft_unset_env(env, data[i]);
	}
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */