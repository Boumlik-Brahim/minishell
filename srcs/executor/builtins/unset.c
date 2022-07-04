/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:22:34 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/04 13:51:35 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_unset_env(t_env **env, char *data)
{
	t_env	*tmp;
	t_env	*current;

	if (ft_strcmp((*env)->key, data) == 0)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp);
	}
	else
	{
		current = *env;
		while (current->next != NULL)
		{
			if (ft_strcmp(current->next->key, data) == 0)
			{
				tmp = current->next;
				current->next = current->next->next;
				free(tmp);
				break ;
			}
			else
				current = current->next;
		}
	}
}

/* -------------------------------------------------------------------------- */

int	ft_chk_unset(char	*data)
{
	int	i;

	if (!ft_isalpha(data[0]))
		return (EXIT_FAILURE);
	i = -1;
	while (data[++i])
	{
		if (!ft_isalnum(data[i]) && data[i] != '_')
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */

int	ft_unset(t_env **env, char **data)
{
	int	i;

	i = 0;
	while (data[++i])
	{
		if (ft_chk_unset(data[i]) == EXIT_SUCCESS)
			ft_unset_env(env, data[i]);
		else
		{
			ft_handle_error("minishell: unset: ", data[i], EXPORT_ERROR);
			g_state.exit_state = 1;
		}
	}
	return (g_state.exit_state);
}

/* -------------------------------------------------------------------------- */