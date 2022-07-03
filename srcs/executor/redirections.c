/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:50:59 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/03 22:56:21 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_heredoc(char *delimiter, t_data *data)
{
	char	*line;
	int		file;

	data->pid = fork();
	g_state.forked = true;
	if (data->pid == -1)
	{
		ft_putendl_fd("FORK ERROR", 2);
		exit(1);
	}
	if (data->pid == 0)
	{
		file = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 00777);
		if (file < 0)
		{
			ft_putstr_fd("OPENING FILE ERROR\n", 1);
			return ;
		}
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
			{
				rl_replace_line("", 1);
				rl_on_new_line();
				free(line);
				break ;
			}
			if (ft_strlen(line) != 0)
			{
				if (ft_strcmp(delimiter, line) == 0)
				{
					free(line);
					break ;
				}
				write(file, line, ft_strlen(line));
			}
			write(file, "\n", 1);
			free(line);
		}
		close(file);
	}
	g_state.forked = false;
}

/* -------------------------------------------------------------------------- */