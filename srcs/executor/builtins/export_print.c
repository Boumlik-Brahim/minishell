/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:51:27 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/05 18:55:08 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

char	**ft_init_exportab(t_env *env)
{
	char	**res;
	int		lstsize;
	int		i;
	t_env	*current;

	lstsize = ft_env_size(env);
	res = (char **)ft_calloc((lstsize + 1), sizeof(char *));
	if (!res)
		return (NULL);
	i = -1;
	current = env;
	while (current)
	{
		res[++i] = ft_strdup(current->key);
		current = current->next;
	}
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

void	ft_exprint(char	*key, char *value, int print)
{
	printf("declare -x %s", key);
	if (print == 1 && value)
		printf("=\"%s\"", value);
	printf("\n");
}

/* -------------------------------------------------------------------------- */

void	ft_print_export(t_env *env)
{
	t_env	*current;
	char	**res;
	int		i;

	res = ft_init_exportab(env);
	ft_sort_exportab(res);
	i = -1;
	while (res[++i])
	{
		current = env;
		while (current)
		{
			if (!ft_strcmp(res[i], current->key) && g_state.empty_env == true)
			{
				if (ft_strcmp(current->key, "PATH")
					&& ft_strcmp(current->key, "_"))
					ft_exprint(current->key, current->value, current->print);
			}
			else if (!ft_strcmp(res[i], current->key))
				ft_exprint(current->key, current->value, current->print);
			current = current->next;
		}
	}
	free_tab(res);
}

/* -------------------------------------------------------------------------- */