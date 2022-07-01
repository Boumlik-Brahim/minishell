#include "../../minishell.h"

void	store_data(t_shell **shell, int *files, t_shell *cmd, t_shell *here_doc)
{
	if (files[0] > -1)
		shelladd_back(shell, shell_new(RED_IN, NULL, NULL, files[0]));
	if (here_doc)
		shelladd_back(shell, here_doc);
	if (files[1] > -1)
		shelladd_back(shell, shell_new(RED_OUT, NULL, NULL, files[1]));
	if (cmd)
		shelladd_back(shell, cmd);
}

void	process_data_util(t_shell **shell, t_token **token, t_env *env)
{
	char	is_cmd;
	int		files[2];
	t_shell *new_cmd;
	t_shell	*here_docs;

	new_cmd = NULL;
	here_docs = NULL;
	files[0] = -2;
	files[1] = -2;
	is_cmd = 0;	
	while (*token && (*token)->token != PIPE)
	{
		if (!new_cmd && (*token)->token == WORD)
			new_cmd = get_cmd(env, *token);
		else if ((*token)->token == RED_IN)
			files[0] = open_file((*token)->content, RED_IN);
		else if ((*token)->token == RED_OUT || (*token)->token == RED_APPEND)
			files[1] = open_file((*token)->content, (*token)->token);
		else if ((*token)->token == HERE_DOC)
			shelladd_back(&here_docs, shell_new(HERE_DOC, \
			ft_strdup((*token)->content), NULL, -1));
		*token = (*token)->next;
	}
	store_data(shell, files, new_cmd, here_docs);
}

char	is_operator(t_token *token)
{
	return ((token->token == RED_IN)
		|| (token->token == RED_OUT)
		|| (token->token == RED_APPEND)
		|| (token->token == HERE_DOC)
		|| (token->token == PIPE));
}

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
	return 0;
}