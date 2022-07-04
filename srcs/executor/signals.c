/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:49:36 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/04 18:08:13 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_state.exit_state = 1;
		ft_putendl_fd("", 1);
		if (g_state.forked == true)
		{
			g_state.exit_state = 130;
			return ;
		}
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/* -------------------------------------------------------------------------- */

void	ft_sigquit_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		g_state.exit_state = 0;
		if (g_state.forked == true)
		{
			g_state.exit_state = 131;
			ft_putendl_fd("Quit: 3", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			return ;
		}
	}
}

/* -------------------------------------------------------------------------- */

void	ft_eof(t_env *env)
{
	g_state.exit_state = 0;
	ft_env_shlvl(env, '-');
	rl_replace_line("", 1);
	ft_putstr_fd("exit\n", 1);
	rl_on_new_line();
}

/* -------------------------------------------------------------------------- */