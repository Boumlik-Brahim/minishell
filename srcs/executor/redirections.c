/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:50:59 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/05 01:03:26 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_heredoc(char *delimiter, t_data *data)
{
	char				*line;
	int					file;

	// g_state.forked = false;
	data->pid = fork();
	if (data->pid == -1)
		return (ft_putendl_fd("FORK ERROR", 2));
	if (data->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		file = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 00777);
		if (file < 0)
		{
			ft_putstr_fd("OPENING FILE ERROR\n", 1);
			exit(1);
		}
		while (1)
		{
			line = readline("> ");
			if (line == NULL || ft_strcmp(delimiter, line) == 0)
				break ;
			if (ft_strlen(line) != 0)
				write(file, line, ft_strlen(line));
			write(file, "\n", 1);
			free(line);
		}
		free(line);
		close(file);
		exit(0);
	}
	// g_state.forked = true;
	signal(SIGQUIT, SIG_IGN);
	waitpid(data->pid, &data->status, 0);
	signal(SIGINT, &ft_sigint_handler);
	signal(SIGQUIT, &ft_sigquit_handler);
	g_state.exit_state = WEXITSTATUS(data->status);
}

/* -------------------------------------------------------------------------- */