/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:38:45 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/06 00:59:05 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	main(int ac, char **av, char **main_env)
{
	char	*line;
	t_env	*env;

	if (ft_strcmp(av[0], "./minishell") == 0 && ac == 1)
	{
		g_state.empty_env = false;
		ft_create_env(&env, main_env);
		g_state.exit_state = EXIT_SUCCESS;
		g_state.forked = 0;
		signal(SIGINT, &ft_sig_handler);
		signal(SIGQUIT, &ft_sig_handler);
		while (1)
		{
			hide_ctrl_char();
			line = readline("minishell$> ");
			if (line == NULL)
			{
				ft_eof(env);
				ft_free_env(env, 0);
				break ;
			}
			if (line[0] != '\0')
				add_history(line);
			parser(line, &env);
			ft_free(line);
		}
		// free_env(&env, 0);
	}
	return (0);
}
