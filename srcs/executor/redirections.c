/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:50:59 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/04 18:50:03 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------------------------------------------------------------- */

// void	ft_heredoc(char *delimiter, t_data *data)
// {
// 	char				*line;
// 	int					file;

// 	data->pid = fork();
// 	//g_state.forked = true;
// 	if (data->pid == -1)
// 	{
// 		ft_putendl_fd("FORK ERROR", 2);
// 		exit(1);	// return (1);
// 	}
// 	if (data->pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// 		file = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 00777);
// 		if (file < 0)
// 		{
// 			ft_putstr_fd("OPENING FILE ERROR\n", 1);
// 			exit(1);
// 		}
// 		while (1)
// 		{
// 			line = readline("> ");
// 			if (line == NULL)
// 			{
// 				rl_replace_line("", 1);
// 				rl_on_new_line();
// 				free(line);
// 				break ;
// 			}
// 			if (ft_strlen(line) != 0)
// 			{
// 				if (ft_strcmp(delimiter, line) == 0)
// 				{
// 					free(line);
// 					break ;
// 				}
// 				write(file, line, ft_strlen(line));
// 			}
// 			write(file, "\n", 1);
// 			free(line);
// 		}
// 		close(file);
// 		exit (0);
// 	}
// 	signal(SIGINT, SIG_IGN);
// 	waitpid(data->pid, NULL, 0);
// 	signal(SIGINT, &ft_sigint_handler);
// 	//g_state.forked = false;
// }

/* -------------------------------------------------------------------------- */
void	hide_ctrl_char(void)
{
	struct termios attr;
	tcgetattr(STDOUT_FILENO, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &attr);
}

void	restore_ctrl_char(void)
{
	struct termios attr;
	tcgetattr(STDOUT_FILENO, &attr);
	attr.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &attr);
}

void	ft_heredoc(char *delimiter, t_data *data)
{
	char				*line;
	int					file;

	g_state.forked = false;
	hide_ctrl_char();
	signal(SIGINT, &ft_sigint_handler);
	data->pid = fork();
	if (data->pid == -1)
		return (ft_putendl_fd("FORK ERROR", 2));
	if (data->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
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
		restore_ctrl_char();
		exit(0);
	}
	g_state.forked = true;
	waitpid(data->pid, NULL, 0);
}

