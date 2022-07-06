/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:16:29 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/02 23:16:32 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

char	is_redirection(t_token *token)
{
	return ((token->token == RED_IN)
		|| (token->token == RED_OUT)
		|| (token->token == RED_APPEND)
		|| (token->token == HERE_DOC));
}

/*----------------------------------------------------------------------------*/

char	check_operators_syntax(t_token *token)
{
	while (token)
	{
		if (is_redirection(token) && !token->content)
			return (1);
		token = token->next;
	}
	return (0);
}

/*----------------------------------------------------------------------------*/

char	check_pipe_syntax(t_token *token)
{
	if (token->token == PIPE || tokenlast(token)->token == PIPE)
		return (put_error("syntax error", \
			"expected token before or after `|'", 258), 1);
	while (token)
	{
		if (token->token == PIPE && token->next && token->next->token == PIPE)
			return (put_error("syntax error", \
				"near unexpected token `|'", 258), 1);
		token = token->next;
	}
	return (0);
}

/*----------------------------------------------------------------------------*/

char	check_errors(t_token *token)
{
	if (!token)
		return (0);
	if (check_operators_syntax(token))
		return (put_error("syntax error", "near unexpected token", 258), 1);
	if (check_pipe_syntax(token))
		return (1);
	return (0);
}
