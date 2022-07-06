/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:15:30 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/05 17:09:55 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

void	free_env(t_env **head, char error)
{
	t_env	*tmp;

	if (*head)
	{
		while (*head)
		{
			tmp = *head;
			*head = (*head)->next;
			ft_free(tmp->key);
			ft_free(tmp->value);
			if (tmp)
				free(tmp);
		}
	}
	if (error)
		ft_putstr_fd("\033[1;31mAllocation failed\033[0m\n", 2);
}

/*----------------------------------------------------------------------------*/

int	ft_env_size(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

/*----------------------------------------------------------------------------*/

int	check_builtins(char *str)
{
	if (ft_tolwr_strcmp(str, "env") == 0)
		return (EXIT_FAILURE);
	else if (ft_tolwr_strcmp(str, "pwd") == 0)
		return (EXIT_FAILURE);
	else if (ft_tolwr_strcmp(str, "echo") == 0)
		return (EXIT_FAILURE);
	else if (ft_tolwr_strcmp(str, "cd") == 0)
		return (EXIT_FAILURE);
	else if (ft_strcmp(str, "export") == 0)
		return (EXIT_FAILURE);
	else if (ft_strcmp(str, "unset") == 0)
		return (EXIT_FAILURE);
	else if (ft_strcmp(str, "exit") == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*----------------------------------------------------------------------------*/

void	put_error(char *keyword, char *msg, int err)
{
	ft_putstr_fd("\033[4;31mMinishell\033[0m: ", 2);
	ft_putstr_fd(keyword, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	g_state.exit_state = err;
}