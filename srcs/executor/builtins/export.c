/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:21:36 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/06 20:38:27 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

int	ft_srch_key(t_env *env, char	*data, int j)
{
	char	*key;
	t_env	*current;

	key = ft_substr(data, 0, j);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(key);
			return (EXIT_SUCCESS);
		}
		current = current->next;
	}
	free(key);
	return (EXIT_FAILURE);
}

/* -------------------------------------------------------------------------- */

int	ft_chk_export(t_env **env, char	*data)
{
	int	i;

	if (data[0] == '#')
		ft_print_export(*env);
	else if (!ft_isalpha(data[0]) && data[0] != '_')
		return (EXIT_FAILURE);
	else
	{
		i = -1;
		while (data[++i])
		{
			if ((data[i] == '+' && data[i + 1] == '=') || (data[i] == '='))
				return (EXIT_SUCCESS);
			else if (!ft_isalnum(data[i]) && data[i] != '_')
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */

void	ft_export_key_value(t_env **env, char **data)
{
	int		i;
	int		j;

	i = 0;
	while (data[++i])
	{
		if (ft_chk_export(env, data[i]) == EXIT_SUCCESS)
		{
			j = 0;
			ft_export_cases(env, data[i], &j);
		}
		else
		{
			ft_handle_error("minishell: export: ", data[i], EXPORT_ERROR);
			g_state.exit_state = 1;
		}
	}
}

/* -------------------------------------------------------------------------- */

int	ft_export(t_env **env, char	**data)
{
	if (!data[1])
	{
		ft_print_export(*env);
		return (g_state.exit_state);
	}
	ft_export_key_value(env, data);
	return (g_state.exit_state);
}

/* -------------------------------------------------------------------------- */