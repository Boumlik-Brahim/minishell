/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backbone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:13:33 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/04 14:11:25 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------------------------------------------------------------- */

int	ft_isbuiltin(char	**data)
{
	if (ft_tolwr_strcmp(data[0], "env") == 0)
		return (EXIT_SUCCESS);
	else if (ft_tolwr_strcmp(data[0], "pwd") == 0)
		return (EXIT_SUCCESS);
	else if (ft_tolwr_strcmp(data[0], "echo") == 0)
		return (EXIT_SUCCESS);
	else if (ft_tolwr_strcmp(data[0], "cd") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(data[0], "export") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(data[0], "unset") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(data[0], "exit") == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

/* -------------------------------------------------------------------------- */

int	ft_exec_builtin(t_env	**env, char	**data)
{
	if (ft_tolwr_strcmp(data[0], "env") == 0)
		g_state.exit_state = ft_env(*env);
	else if (ft_tolwr_strcmp(data[0], "pwd") == 0)
		g_state.exit_state = ft_pwd(data);
	else if (ft_tolwr_strcmp(data[0], "echo") == 0)
		g_state.exit_state = ft_echo(data);
	else if (ft_tolwr_strcmp(data[0], "cd") == 0)
		g_state.exit_state = ft_cd(*env, data);
	else if (ft_strcmp(data[0], "export") == 0)
		g_state.exit_state = ft_export(env, data);
	else if (ft_strcmp(data[0], "unset") == 0)
		g_state.exit_state = ft_unset(env, data);
	else if (ft_strcmp(data[0], "exit") == 0)
		ft_exit(*env, data);
	return (g_state.exit_state);
}

/* -------------------------------------------------------------------------- */