/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:28:15 by bbrahim           #+#    #+#             */
/*   Updated: 2022/06/29 18:35:02 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

static int	ft_is_space(char c)
{
	if (c == '\t' || c == '\n'
		|| c == '\r' || c == '\v'
		|| c == ' ' || c == '\f')
	{
		return (1);
	}
	return (0);
}

uint8_t	ft_exit_atoi(const char *str)
{
	uint8_t		res;
	uint8_t		sign;
	size_t		i;

	res = 0;
	i = 0;
	sign = 1;
	while (ft_is_space(str[i]) != 0)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

/* -------------------------------------------------------------------------- */

void	ft_chk_exit_args(char **data)
{
	int		ex_stat;

	if (data[2] != NULL)
	{
		ft_putstr_fd("minishell$>: exit: too many arguments\n", 2);
		g_state.exit_state = EXIT_FAILURE;
	}
	else
	{
		ex_stat = ft_exit_atoi(data[1]);
		g_state.exit_state = ex_stat;
	}
}

/* -------------------------------------------------------------------------- */

int	ft_chk_exit(char *data)
{
	int	i;

	i = 0;
	if (data[i] == '+' || data[i] == '-')
		i++;
	while (data[i])
	{
		if (!ft_isdigit(data[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */

int	ft_exit(t_env *env, char **data)
{
	ft_env_shlvl(env, '-');
	printf("exit\n");
	if (!data[1])
		g_state.exit_state = EXIT_SUCCESS;
	if (data[1] != NULL)
	{
		if (ft_chk_exit(data[1]) == EXIT_SUCCESS)
			ft_chk_exit_args(data);
		else
		{
			ft_handle_error("minishell$>: exit: ", data[1], EXIT_ERROR);
			g_state.exit_state = 255;
		}
	}
	return (g_state.exit_state);
}

/* -------------------------------------------------------------------------- */