/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:38:45 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/04 18:47:06 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	put_error(char *keyword, char *err)
{
	ft_putstr_fd("\033[4;31mMinishell\033[0m: ", 2);
	ft_putstr_fd(keyword, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
}

int	main(int ac, char **av, char **main_env)
{
	char		*line;
	t_shell		*shell;
	t_env		*env;

	if (ft_strcmp(av[0], "./minishell") == 0 && ac == 1)
	{
		g_state.empty_env = false;
		ft_create_env(&env, main_env);
		g_state.exit_state = EXIT_SUCCESS;
		g_state.forked = false;
		signal(SIGINT, &ft_sigint_handler);
		signal(SIGQUIT, &ft_sigquit_handler);
		// rl_catch_signals = 0;
		while (1)
		{
			line = readline("minishell$> ");
			if (line == NULL)
			{
				ft_eof(env);
				ft_free_env(env, 0);
				break ;
			}
			if (line[0] != '\0')
				add_history(line);
			shell = parser(line, &env);
			if (!shell)
				ft_putstr_fd("\033[1;31mSyntax error\033[0m\n", 2);
		}
	}
	return (0);
}
