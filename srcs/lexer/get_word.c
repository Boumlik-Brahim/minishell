#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

char	get_word_util(char **s1, char **s2)
{
	if (!*s1)
	{
		*s1 = ft_strdup(*s2);
		ft_free(*s2);
	}
	else
		*s1 = ft_realloc(*s1, *s2);
	if (!s1)
		return (1);
	s2 = NULL;
	return (0);
}

/*----------------------------------------------------------------------------*/

char get_word(t_token **token, char *line, int *i, t_env *env)
{
	char	*content;
	char	*result;
 
	content = NULL;
	result = NULL;
	while(ft_isascii(line[*i]) && !ft_strchr("#&();|<> \\`~", line[*i]))
	{
		if (line[*i] == '\"')
		{
			*i += 1;
			content = word_within_dqoutes(line, i, env, *token);
		}
		else if (line[*i] == '\'')
			content = word_within_sqoutes(line, i);
		else if (!check_last(*token, HERE_DOC) && line[*i] == '$' \
			&& ft_isalnum(line[*i + 1]))
			content = expender(line, i, env);
		else
			content = word(line, i);
		get_word_util(&result, &content);
	}
	tokenadd_back(token, tokennew(result, WORD));
	return (0);
}