/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:42:57 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/02 23:43:02 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

void	free_path(char **path)
{
	int	i;

	i = 0;
	if (path)
	{
		while (path[i])
			free(path[i++]);
		free(path);
	}
}

/*----------------------------------------------------------------------------*/

char	**get_path(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			return (ft_split(env->value, ':'));
		}
		env = env->next;
	}
	return (NULL);
}

/*----------------------------------------------------------------------------*/

char	check_cmd_permissions(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (filetype(cmd))
			return (1);
		else if (access(cmd, X_OK) == 0)
			return (0);
		else
		{
			put_error(cmd, "Permission denied", 1);
			return (1);
		}
	}
	put_error(cmd, "No such file or directory", 1);
	return (1);
}
