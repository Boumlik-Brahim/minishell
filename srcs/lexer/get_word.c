/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:24:57 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/06 23:52:19 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

char	is_expandable(char *line, int i)
{
	if (line[i] == '$' && (ft_isalnum(line[i +1]) || line[i +1] == '_'))
		return (1);
	return (0);
}

/*----------------------------------------------------------------------------*/

char	get_word_util(char **s1, char **s2)
{
	if (!*s2)
		return (0);
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

char	get_word(t_token **token, char *line, int *i, t_env *env)
{
	char	*content;
	char	*result;

	content = NULL;
	result = NULL;
	while (ft_isascii(line[*i]) && !ft_strchr("| <>", line[*i]))
	{
		if (line[*i] == '\"')
		{
			*i += 1;
			content = word_within_dqoutes(line, i, env, *token);
		}
		else if (line[*i] == '\'')
			content = word_within_sqoutes(line, i);
		else if (!check_last(*token, HERE_DOC) && is_expandable(line, *i))
			content = expender(line, i, env);
		else if (ft_isascii(line[*i]) && !ft_strchr("| <>", line[*i]))
			content = word(line, i);
		if (get_word_util(&result, &content))
			return (1);
	}
	if (result)
		tokenadd_back(token, tokennew(result, WORD));
	return (0);
}
