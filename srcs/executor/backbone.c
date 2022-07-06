/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backbone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:13:33 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/06 22:26:25 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_subforkcmd(t_env **env, t_shell *shell, t_data *data)
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
		close(data->fd[0]);
		close(data->fd[1]);
		ft_executecmd(shell, data->env_tab);
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