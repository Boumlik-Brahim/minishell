/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:17:44 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/06 01:56:10 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	ft_wait_process(t_data *data)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (waitpid(data->pid, &data->status, 0) > 0)
	{
		if (WIFEXITED(data->status))
			g_state.exit_state = WEXITSTATUS(data->status);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	signal(SIGINT, &ft_sig_handler);
	signal(SIGQUIT, &ft_sig_handler);
}

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
}

/* -------------------------------------------------------------------------- */

void	ft_forkcmd(t_env **env, t_shell *shell, t_data *data)
{
	pipe(data->fd);
	data->pid = fork();
	g_state.forked = 1;
	if (data->pid == -1)
		exit(1);
	if (data->pid == 0)
	{
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
	if (shell->next == NULL && data->pid > 0)
		ft_wait_process(data);
}

/* -------------------------------------------------------------------------- */

void	ft_sample_cmd(t_env **env, t_shell *shell, t_data *data)
{
	while (shell)
	{
		if (shell->token == CMD && data->valid == 0)
		{
			ft_forkcmd(env, shell, data);
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
		else if (shell->token == INVALID_FILE)
			data->valid = 1;
		else if (shell->token == PIPE)
			data->valid = 0;
		shell = shell->next;
	}
}

/* -------------------------------------------------------------------------- */

void	ft_sample_cmd_builtin(t_env **env, t_shell *shell, t_data *data)
{
	while (shell)
	{
		if (shell->token == RED_IN)
			data->in_fd = shell->file;
		else if (shell->token == CMD
			&& !ft_isbuiltin(shell->switchs) && data->valid == 0)
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
		else if (shell->token == INVALID_FILE)
			data->valid = 1;
		shell = shell->next;
	}
}

/* -------------------------------------------------------------------------- */

int	ft_ms_backbone(t_env **env, t_shell *shell, t_data *data)
{
	data->valid = 0;
	data->in_fd = 0;
	data->in_def = dup(STDIN_FILENO);
	data->out_def = dup(STDOUT_FILENO);
	if (ft_is_only_builtin(shell) == EXIT_SUCCESS)
		ft_sample_cmd_builtin(env, shell, data);
	else
	{
		ft_sample_cmd(env, shell, data);
		g_state.forked = 0;
	}
	unlink(".tmp");
	return (EXIT_SUCCESS);
}

/* -------------------------------------------------------------------------- */
