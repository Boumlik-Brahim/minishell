/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:38:45 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/06 23:59:02 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_init_global(t_env	**env, char	**main_env)
{
	g_state.empty_env = false;
	g_state.exit_state = EXIT_SUCCESS;
	g_state.forked = 0;
	ft_create_env(env, main_env);
	signal(SIGINT, &ft_sig_handler);
	signal(SIGQUIT, &ft_sig_handler);
}

int	main(int ac, char **av, char **main_env)
{
	char	*line;
	t_env	*env;

	(void)ac;
	(void)av;
	ft_init_global(&env, main_env);
	while (1)
	{
		hide_ctrl_char();
		line = readline("Minishell> ");
		if (!line)
			break ;
		else if (line[0] == '\n')
		{
			ft_free(line);
			continue ;
		}
		if (line[0] != '\0')
			add_history(line);
		parser(line, &env);
		ft_free(line);
	}
	free_env(&env, 0);
	ft_eof(env);
	return (0);
}
