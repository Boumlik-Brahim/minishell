/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:17:44 by bbrahim           #+#    #+#             */
/*   Updated: 2022/06/30 20:47:32 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/* -------------------------------------------------------------------------- */

int	ft_executecmd(t_shell *shell, char	**env_tab)
{
	g_state.exit_state = execve(shell->data, shell->switchs, env_tab);
	if (g_state.exit_state == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		g_state.exit_state = 126;
		exit(g_state.exit_state);
	}
	exit(1);
	return (EXIT_SUCCESS);
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

int	ft_ms_backbone(t_env	*env, t_shell *shell, t_data *data)
{
	data->in_fd = 0;
	while (shell)
	{
		if (shell->token == CMD)
		{
			pipe(data->fd);
			if (ft_isbuiltin(shell->switchs) == EXIT_SUCCESS)
			{
				g_state.forked = true;
				data->pid = fork();
				if (data->pid == -1)
				{
					ft_putendl_fd("FORK ERROR", 2);
					exit (1);
				}
				if (data->pid == 0)
				{
					if (shell->next && shell->next->token == PIPE)
						ft_dup(shell, data->in_fd, data->fd, 1);
					else
						ft_dup(shell, data->in_fd, data->fd, 0);
					ft_exec_builtin(env, shell->switchs);
				}
				waitpid(data->pid, NULL, 0);
				close(data->fd[1]);
				data->in_fd = data->fd[0];
			}
			else
			{
				g_state.forked = true;
				data->pid = fork();
				if (data->pid == -1)
				{
					ft_putendl_fd("FORK ERROR", 2);
					exit (1);
				}
				if (data->pid == 0)
				{
					data->env_tab = ft_env_table(env);
					if (shell->next && shell->next->token == PIPE)
						ft_dup(shell, data->in_fd, data->fd, 1);
					else
						ft_dup(shell, data->in_fd, data->fd, 0);
					ft_executecmd(shell, data->env_tab);
				}
				waitpid(data->pid, NULL, 0);
				close(data->fd[1]);
				data->in_fd = data->fd[0];
			}
		}
		else if (shell->token == RED_IN)
			data->in_fd = shell->file;
		else if (shell->token == HERE_DOC)
		{
			ft_heredoc(shell->data);
			data->in_fd = open(".tmp", O_RDONLY, 00777);
		}
		shell = shell->next;
	}
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */