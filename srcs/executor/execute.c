/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:17:44 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/05 01:24:38 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/* -------------------------------------------------------------------------- */

void	ft_executecmd(t_shell *shell, char	**env_tab)
{
	restore_ctrl_char();
	g_state.exit_state = execve(shell->data, shell->switchs, env_tab);
	if (g_state.exit_state == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		g_state.exit_state = 126;
		exit(g_state.exit_state);
	}
	exit(0);
}

/* -------------------------------------------------------------------------- */

void	ft_dup(t_shell *shell, int in_fd, int *fd, int i)
{
	if (i == 1)
	{
		if (shell->prev && shell->prev->token == RED_OUT)
		{
			dup2(in_fd, 0);
			dup2(shell->prev->file, 1);
			return ;
		}
		else
		{
			dup2(in_fd, 0);
			dup2(fd[1], 1);
			return ;
		}
	}
	else
	{
		if (shell->prev && shell->prev->token == RED_OUT)
		{
			dup2(in_fd, 0);
			dup2(shell->prev->file, 1);
			return ;
		}
		else
			dup2(in_fd, 0);
	}
}

/* -------------------------------------------------------------------------- */

int	ft_is_only_builtin(t_shell *shell)
{
	while (shell)
	{
		if (shell->token == CMD)
		{
			if (shell->next && shell->next->token == PIPE)
				return (EXIT_FAILURE);
			else if (ft_isbuiltin(shell->switchs) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
			else
				return (EXIT_FAILURE);
		}
		shell = shell->next;
	}
	return (EXIT_FAILURE);
}

/* -------------------------------------------------------------------------- */

int	ft_ms_backbone(t_env **env, t_shell *shell, t_data *data)
{
	data->in_fd = 0;
	data->in_def = dup(STDIN_FILENO);
	data->out_def = dup(STDOUT_FILENO);
	if (ft_is_only_builtin(shell) == EXIT_SUCCESS)
	{
		while (shell)
		{
			if (shell->token == RED_IN)
				data->in_fd = shell->file;
			else if (shell->token == CMD && !ft_isbuiltin(shell->switchs))
			{
				if (shell->prev && shell->prev->token == RED_OUT)
				{
					dup2(data->in_fd, 0);
					dup2(shell->prev->file, 1);
				}
				else
					dup2(data->in_fd, 0);
				ft_exec_builtin(env, shell->switchs);
				dup2(data->in_def, 0);
				dup2(data->out_def, 1);
			}
			shell = shell->next;
		}
	}
	else
	{
		while (shell)
		{
			if (shell->token == CMD)
			{
				pipe(data->fd);
				data->pid = fork();
				// hide_ctrl_char();
				// g_state.forked = true;
				if (data->pid == -1)
				{
					ft_putendl_fd("FORK ERROR", 2);
					exit(1);
				}
				if (data->pid == 0)
				{
					// g_state.forked = false;
					dup2(data->in_fd, 0);
					if (shell->prev && shell->prev->token == RED_OUT)
						dup2(shell->prev->file, 1);
					else if (shell->next && shell->next->token == PIPE)
						dup2(data->fd[1], 1);
					if (!ft_isbuiltin(shell->switchs))
					{
						ft_exec_builtin(env, shell->switchs);
						exit (0);
					}
					else
					{
						data->env_tab = ft_env_table(*env);
						ft_executecmd(shell, data->env_tab);
					}
				}
				if (shell->next == NULL)
				{
					waitpid(data->pid, &data->status, 0);
					g_state.exit_state = WEXITSTATUS(data->status);
				}
				close(data->fd[1]);
				if (data->in_fd != 0)
					close(data->in_fd);
				data->in_fd = data->fd[0];
			}
			else if (shell->token == RED_IN)
				data->in_fd = shell->file;
			else if (shell->token == HERE_DOC)
			{
				ft_heredoc(shell->data, data);
				data->in_fd = open(".tmp", O_RDONLY, 00777);
			}
			shell = shell->next;
		}
		// signal(SIGINT, SIG_IGN);
		// g_state.forked = false;
		signal(SIGINT, &ft_sigint_handler);
		signal(SIGQUIT, &ft_sigquit_handler);
		while (waitpid(-1, NULL, 0) > 0)
			;
	}
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */
