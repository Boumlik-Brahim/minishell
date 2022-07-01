/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:21:36 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/01 18:34:23 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_print_export(t_env *env, char **res)
{
	t_env	*current;
	int		i;

	i = -1;
	while (res[++i])
	{
		current = env;
		while (current)
		{
			if (ft_strcmp(res[i], current->key) == 0)
			{
				printf("declare -x %s", current->key);
				if (current->print == 1)
					printf("=\"%s\"", current->value);
				printf("\n");
			}
			current = current->next;
		}
	}
}

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

int	ft_chk_export(char	*data)
{
	int	i;

	if (*data == '=')
		return (EXIT_FAILURE);
	// if (*data == '#')
	// 	ft_print_export(env);
	i = -1;
	while (data[++i] && data[i] != '=')
	{
		if (!ft_isalpha(data[i]) && data[i] != '_')
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */

void	ft_export_key_value(t_env *env, char	**data)
{
	int		j;
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (data[++i])
	{
		if (ft_chk_export(data[i]) == EXIT_SUCCESS)
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
	}
}

/* -------------------------------------------------------------------------- */

char	**ft_init_exportab(t_env *env)
{
	char	**res;
	int		lstsize;
	int		i;
	t_env	*current;

	lstsize = ft_env_size(env);
	res = (char **)malloc(sizeof(char *) * (lstsize + 1));
	if (!res)
		return (NULL);
	i = -1;
	current = env;
	while (current)
	{
		res[++i] = ft_strdup(current->key);
		current = current->next;
	}
	res[i] = NULL;
	return (res);
}

/* -------------------------------------------------------------------------- */

void	ft_sort_exportab(char **res)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (res[++i])
	{
		j = -1;
		while (res[++j])
		{
			if (ft_strcmp(res[j], res[i]) > 0)
			{
				tmp = res[i];
				res[i] = res[j];
				res[j] = tmp;
			}
		}
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
	// ft_export_key_value(env, data);
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */