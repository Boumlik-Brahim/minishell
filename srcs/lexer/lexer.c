/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:29:45 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/02 23:29:46 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

void	print_token(t_token *token)
{
	while (token)
	{
		printf("token:%d:   value:%s:\n", token->token, token->content);
		token = token->next;
	}
}

/*----------------------------------------------------------------------------*/

t_token	*lexer(char *line, t_env *env)
{
	t_token	*token;

	token = NULL;
	if (check_qoutes(line))
		return (NULL);
	if (tokenizer(&token, line, env))
	{
		token_clear(&token);
		put_error("Uknown", "Parse error", 258);
		return (NULL);
	}
	if (check_errors(token))
	{
		token_clear(&token);
		return (NULL);
	}
	return (token);
}
