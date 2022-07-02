/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:21:36 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/02 19:04:11 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_export_env(t_env **env, char	*data, int j, int p)
{
	char	*key;
	char	*value;

	key = ft_strdup(ft_substr(data, 0, j));
	value = ft_strdup(ft_strchr(data, '=') + 1);
	ft_envadd_back(env, ft_envnew(key, value, p));
}

/* -------------------------------------------------------------------------- */

void	ft_add_value(t_env **env, char	*data, int j, int i)
{
	t_env	*current;
	char	*key;
	char	*value;

	key = ft_substr(data, 0, j);
	if (i == 1)
	{
		value = ft_strchr(data, '=') + 1;
		current = *env;
		while (current)
		{
			if (ft_strcmp(current->key, key) == 0)
			{
				current->value = ft_strjoin(current->value, value);
			}
			current = current->next;
		}
	}
	else if (i == 0)
	{
		current = *env;
		while (current)
		{
			if (ft_strcmp(current->key, key) == 0)
			{
				if (!current->value)
					current->value = ft_strdup(ft_strchr(data, '=') + 1);
				else
				{
					free(current->value);
					current->value = ft_strdup(ft_strchr(data, '=') + 1);
				}
			}
			current = current->next;
		}
	}
}

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
			return (EXIT_SUCCESS);
		current = current->next;
	}
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
			while (data[i][j] != '+' && data[i][j] != '=')
				j++;
			if (data[i][j] == '+' && data[i][j + 1] == '=')
			{
				if (ft_srch_key(*env, data[i], j) == EXIT_SUCCESS)
					ft_add_value(env, data[i], j, 1);
				else
					ft_export_env(env, data[i], j, 1);
			}
			else if (data[i][j] == '=')
			{
				if (ft_srch_key(*env, data[i], j) == EXIT_SUCCESS)
					ft_add_value(env, data[i], j, 0);
				else
					ft_export_env(env, data[i], j, 1);
			}
			else
			{
				if (ft_srch_key(*env, data[i], j) == EXIT_SUCCESS)
					break ;
				else
					ft_export_env(env, data[i], j, 1);
			}
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