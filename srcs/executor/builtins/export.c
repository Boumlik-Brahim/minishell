/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:21:36 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/01 21:25:48 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_export_env(t_env *env, char *key, char *value, bool p)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(key);
			if (ft_strcmp(current->value, value) != 0)
			{
				free(current->value);
				current->value = value;
				return ;
			}
			else
			{
				free(value);
				return ;
			}
		}
		current = current->next;
	}
	ft_envadd_back(&env, ft_envnew(key, value, p));
}

/* -------------------------------------------------------------------------- */

int	ft_chk_export(t_env *env, char	*data, char	**res)
{
	int	i;

	if (*data == '#')
		ft_print_export(env, res);
	else if (*data == '=')
		return (EXIT_FAILURE);
	else
	{
		i = -1;
		while (data[++i] && data[i] != '=')
		{
			if (!ft_isalpha(data[i]) && data[i] != '_')
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */

void	ft_export_key_value(t_env *env, char **data, char **res)
{
	int		j;
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (data[++i])
	{
		if (ft_chk_export(env, data[i], res) == EXIT_SUCCESS)
		{
			j = 0;
			while (data[i][j] != '=' && data[i][j])
				j++;
			key = ft_substr(data[i], 0, j);
			if (data[i][j] == '=' && data[i][j + 1] != '\0')
			{
				value = ft_strdup(&data[i][j + 1]);
				ft_export_env(env, key, value, 1);
			}
			else
				ft_export_env(env, key, value, 0);
		}
		else
			ft_handle_error("minishell: export: ", data[i], EXPORT_ERROR);
	}
}

/* -------------------------------------------------------------------------- */

int	ft_export(t_env *env, char	**data)
{
	char	**res;

	res = ft_init_exportab(env);
	ft_sort_exportab(res);
	if (!data[1])
	{
		ft_print_export(env, res);
		return (EXIT_SUCCESS);
	}
	ft_export_key_value(env, data, res);
	free_tab(res);
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */