/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:50:47 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/02 23:50:49 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

void	store_data(t_shell **shell, int *args, t_shell *cmd, t_shell *here_doc)
{
	if (args[2])
	{
		if (args[0] > -1)
			shelladd_back(shell, shell_new(RED_IN, NULL, NULL, args[0]));
		else if (args[0] == -1)
			shelladd_back(shell, shell_new(INVALID_FILE, NULL, NULL, args[0]));
		if (here_doc)
			shelladd_back(shell, here_doc);
	}
	else
	{
		if (here_doc)
			shelladd_back(shell, here_doc);
		if (args[0] > -1)
			shelladd_back(shell, shell_new(RED_IN, NULL, NULL, args[0]));
		else if (args[0] == -1)
			shelladd_back(shell, shell_new(INVALID_FILE, NULL, NULL, args[0]));
	}
	if (args[1] > -1)
		shelladd_back(shell, shell_new(RED_OUT, NULL, NULL, args[1]));
	else if (args[1] == -1)
		shelladd_back(shell, shell_new(INVALID_FILE, NULL, NULL, args[1]));
	if (cmd)
		shelladd_back(shell, cmd);
}

/*----------------------------------------------------------------------------*/

void	init_vars(int *args, t_shell **new_cmd, t_shell **here_docs)
{
	args[0] = -2;
	args[1] = -2;
	args[2] = 0;
	*new_cmd = NULL;
	*here_docs = NULL;
}

/*----------------------------------------------------------------------------*/

void	process_data_util(t_shell **shell, t_token **token, t_env *env)
{
	int		args[3];
	t_shell	*new_cmd;
	t_shell	*here_docs;

	init_vars(args, &new_cmd, &here_docs);
	while (*token && (*token)->token != PIPE)
	{
		if (!new_cmd && (*token)->token == WORD)
			new_cmd = get_cmd(env, *token);
		else if ((*token)->token == RED_IN)
			handle_files(args, (*token)->content, RED_IN);
		else if ((*token)->token == RED_OUT || (*token)->token == RED_APPEND)
			handle_files(args, (*token)->content, (*token)->token);
		else if ((*token)->token == HERE_DOC)
		{
			args[2] = 1;
			shelladd_back(&here_docs, shell_new(HERE_DOC, \
			ft_strdup((*token)->content), NULL, -1));
		}
		*token = (*token)->next;
	}
	store_data(shell, args, new_cmd, here_docs);
}

/*----------------------------------------------------------------------------*/

char	is_operator(t_token *token)
{
	return ((token->token == RED_IN)
		|| (token->token == RED_OUT)
		|| (token->token == RED_APPEND)
		|| (token->token == HERE_DOC)
		|| (token->token == PIPE));
}

/*----------------------------------------------------------------------------*/

char	process_data(t_shell **shell, t_token *token, t_env *env)
{
	char	is_cmd;

	is_cmd = 0;
	*shell = NULL;
	while (token)
	{
		process_data_util(shell, &token, env);
		if (token && token->token == PIPE)
			shelladd_back(shell, shell_new(PIPE, NULL, NULL, -1));
		if (token)
			token = token->next;
	}
	return (0);
}
/*----------------------------------------------------------------------------*/
