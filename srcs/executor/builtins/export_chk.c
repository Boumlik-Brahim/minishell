/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_chk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 21:29:22 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/02 22:23:59 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_export_env(t_env **env, char	*data, int j, int p)
{
	char	*key;
	char	*value;
	char	*sep;

	key = ft_substr(data, 0, j);
	value = NULL;
	sep = ft_strchr(data, '=');
	if (sep)
		value = ft_strdup(sep + 1);
	ft_envadd_back(env, ft_envnew(key, value, p));
}

/* -------------------------------------------------------------------------- */

void	ft_add_value(t_env **env, char	*data, int j)
{
	t_env	*current;
	char	*key;

	key = ft_substr(data, 0, j);
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

/* -------------------------------------------------------------------------- */

void	ft_join_value(t_env **env, char	*data, int j)
{
	t_env	*current;
	char	*key;
	char	*value;

	key = ft_substr(data, 0, j);
	value = ft_strchr(data, '=') + 1;
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			current->value = ft_strjoin(current->value, value);
		current = current->next;
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