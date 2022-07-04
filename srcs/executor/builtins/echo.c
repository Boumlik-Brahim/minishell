/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:29:02 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/04 14:00:54 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_print_echo(char	**data, int *i)
{
	if (*i > 1)
	{
		while (data[*i])
		{
			printf("%s", data[*i]);
			if (data[*i + 1] != NULL)
				printf(" ");
			(*i)++;
		}
	}
	else
	{
		while (data[*i])
		{
			printf("%s", data[*i]);
			if (data[*i + 1])
				printf(" ");
			(*i)++;
		}
		printf("\n");
	}
}

/* -------------------------------------------------------------------------- */

int	ft_chk_echo(char	*data)
{
	int	i;

	if (data[0] == '-' && data[1] == 'n')
	{
		i = 1;
		while (data[++i])
		{
			if (data[i] != 'n')
				return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/* -------------------------------------------------------------------------- */

int	ft_echo(char	**data)
{
	int	i;

	if (!data[1])
		printf("");
	else if (ft_strcmp(data[1], "$?") == 0)
		printf("%d\n", g_state.exit_state);
	else
	{
		i = 1;
		while (data[i] && ft_chk_echo(data[i]) == EXIT_SUCCESS)
			i++;
		ft_print_echo(data, &i);
	}
	return (g_state.exit_state);
}

/* -------------------------------------------------------------------------- */