/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:21:36 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/02 22:23:50 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_export_cases(t_env **env, char *data, int *j)
{
	while (data[*j] && data[*j] != '+' && data[*j] != '=')
		(*j)++;
	if (data[*j] == '+' && data[*j + 1] == '=')
	{
		if (ft_srch_key(*env, data, *j) == EXIT_SUCCESS)
			ft_join_value(env, data, *j);
		else
			ft_export_env(env, data, *j, 1);
	}
	else if (data[*j] == '=')
	{
		if (ft_srch_key(*env, data, *j) == EXIT_SUCCESS)
			ft_add_value(env, data, *j);
		else
			ft_export_env(env, data, *j, 1);
	}
	else
	{
		if (ft_srch_key(*env, data, *j) == EXIT_SUCCESS)
			return ;
		else
			ft_export_env(env, data, *j, 1);
	}
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
			ft_handle_error("minishell: export: ", data[i], EXPORT_ERROR);
	}
}

/* -------------------------------------------------------------------------- */

int	ft_export(t_env **env, char	**data)
{
	if (!data[1])
	{
		ft_print_export(*env);
		return (EXIT_SUCCESS);
	}
	ft_export_key_value(env, data);
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */