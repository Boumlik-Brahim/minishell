/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_chk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 21:29:22 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/05 20:46:20 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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