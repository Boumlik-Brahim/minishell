/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:30:10 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/06 16:34:41 by bbrahim          ###   ########.fr       */
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

void	ft_cd_home(t_env *env, char **data)
{
	char	*str;

	str = ft_getenv(env, "HOME");
	if (str && *str)
	{
		if (chdir(str) == -1)
		{
			ft_handle_errorcd("minishell: cd: ", data[1], CHDIR_ERROR);
			g_state.exit_state = 1;
		}
	}
	else
	{
		ft_handle_errorcd("minishell: cd", data[1], CD_HOME_ERROR);
		g_state.exit_state = 1;
	}
	free(str);
}

/* -------------------------------------------------------------------------- */

int	ft_cd(t_env *env, char **data)
{
	char	cwd[PATH_MAX];

	if (data[1] != NULL)
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			perror(CD_ERROR);
			return (g_state.exit_state);
		}
		ft_cd_oldwd(env, cwd);
		if (chdir(data[1]) == -1)
		{
			ft_handle_errorcd("minishell: cd: ", data[1], CHDIR_ERROR);
			g_state.exit_state = 1;
		}
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			perror(CD_ERROR);
			return (g_state.exit_state);
		}
		ft_cd_wd(env, cwd);
	}
	else
		ft_cd_home(env, data);
	return (g_state.exit_state);
}

/* -------------------------------------------------------------------------- */