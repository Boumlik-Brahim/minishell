/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:49:36 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/06 00:55:42 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------------------------------------------------------------- */

void	hide_ctrl_char(void)
{
	struct termios	attr;

	tcgetattr(STDOUT_FILENO, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &attr);
}

/* -------------------------------------------------------------------------- */

void	restore_ctrl_char(void)
{
	struct termios	attr;

	tcgetattr(STDOUT_FILENO, &attr);
	attr.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &attr);
}

/* -------------------------------------------------------------------------- */

void	ft_sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_state.exit_state = 1;
		ft_putendl_fd("", 1);
		if (g_state.forked == 1)
		{
			g_state.exit_state = 128 + signal;
			return ;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		if (g_state.forked == 1)
		{
			g_state.exit_state = 128 + signal;
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
	restore_ctrl_char();
}

/* -------------------------------------------------------------------------- */