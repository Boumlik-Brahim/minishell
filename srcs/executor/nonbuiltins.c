/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonbuiltins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:13:33 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/01 13:39:18 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------------------------------------------------------------- */

int	ft_tolwr_strcmp(char *s1, char *s2)
{
	unsigned char	*us1;
	unsigned char	*us2;
	int				i;

	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	i = 0;
	while (us1[i] && ft_tolower(us1[i]) == ft_tolower(us2[i]))
		i++;
	return (us1[i] - us2[i]);
}

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

int	ft_exec_builtin(t_env	*env, char	**data)
{
	if (ft_tolwr_strcmp(data[0], "env") == 0)
		ft_env(env);
	else if (ft_tolwr_strcmp(data[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_tolwr_strcmp(data[0], "echo") == 0)
		ft_echo(data);
	else if (ft_tolwr_strcmp(data[0], "cd") == 0)
		ft_cd(env, data);
	else if (ft_strcmp(data[0], "export") == 0)
		ft_export(env, data);
	else if (ft_strcmp(data[0], "unset") == 0)
		ft_unset(env, data);
	else if (ft_strcmp(data[0], "exit") == 0)
		ft_exit(env, data);
	return (EXIT_FAILURE);
}

/* -------------------------------------------------------------------------- */