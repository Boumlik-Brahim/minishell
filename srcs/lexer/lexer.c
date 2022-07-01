#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

// static void print_token(t_token *token)
// {
// 	while (token)
// 	{
// 		printf("token:%d:   value:%s:\n",token->token, token->content);
// 		token = token->next;
// 	}
// }

/*----------------------------------------------------------------------------*/

t_token *lexer(char *line, t_env *env)
{
	t_token	*token;

	token = NULL;
	if (check_errors(line))
		return (NULL);
	if (tokenizer(&token, line, env))
		return (NULL);
	// print_token(token);
	return (token);
}
