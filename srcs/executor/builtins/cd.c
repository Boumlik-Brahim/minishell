/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:30:10 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/01 15:33:08 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_cd_wd(t_env *env, char *cwd)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(cwd);
			return ;
		}
		current = current->next;
	}
}

/* -------------------------------------------------------------------------- */

void	ft_cd_oldwd(t_env *env, char *oldwd)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(oldwd);
			return ;
		}
		current = current->next;
	}
}

/* -------------------------------------------------------------------------- */

int	ft_cd(t_env *env, char **data)
{
	char	cwd[PATH_MAX];

	if (data[1] != NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
			perror("getcwd");
		ft_cd_oldwd(env, cwd);
		if (chdir(data[1]) == -1)
			return (EXIT_FAILURE);
		if (getcwd(cwd, PATH_MAX) == NULL)
			perror(CD_ERROR);
		ft_cd_wd(env, cwd);
	}
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */