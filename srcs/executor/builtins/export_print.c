/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:51:27 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/02 20:19:15 by bbrahim          ###   ########.fr       */
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
			if (ft_strcmp(res[i], current->key) == 0)
			{
				printf("declare -x %s", current->key);
				if (current->print == 1 && current->value)
					printf("=\"%s\"", current->value);
				printf("\n");
			}
			current = current->next;
		}
	}
	free_tab(res);
}

/* -------------------------------------------------------------------------- */