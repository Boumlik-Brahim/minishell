/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:22:43 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/02 23:22:45 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expender(char *line, int *i, t_env *env)
{
	char	*buffer;
	char	*res;
	int		len;
	int		start;

	len = 0;
	*i += 1;
	start = *i;
	buffer = NULL;
	while (line[*i])
	{
		if (!ft_isalnum(line[*i]) && line[*i] != '_')
			break ;
		len++;
		*i += 1;
	}
	buffer = ft_substr(line, start, len);
	res = ft_getenv(env, buffer);
	ft_free(buffer);
	return (res);
}

/*----------------------------------------------------------------------------*/

static	char	*get_chunk(char *line, int *i)
{
	int	len;
	int	start;

	len = 0;
	start = *i;
	while (line[*i])
	{
		if (len && ft_strchr("$\"", line[*i]))
			break ;
		len++;
		*i += 1;
	}
	return (ft_substr(line, start, len));
}

/*----------------------------------------------------------------------------*/

char	*word_within_dqoutes(char *line, int *i, t_env *env, t_token *token)
{
	char	*string;
	char	*substring;

	string = NULL;
	substring = NULL;
	while (line[*i])
	{
		if (line[*i] == '\"')
		{
			*i += 1;
			break ;
		}
		if (!check_last(token, HERE_DOC) && line[*i] == '$')
			substring = expender(line, i, env);
		else
			substring = get_chunk(line, i);
		if (!string)
		{
			string = ft_strdup(substring);
			ft_free(substring);
		}
		else if (substring)
			string = ft_realloc(string, substring);
	}
	return (string);
}

/*----------------------------------------------------------------------------*/

char	*word_within_sqoutes(char *line, int *i)
{
	int	len;
	int	start;

	len = 0;
	*i += 1;
	start = *i;
	while (line[*i])
	{
		if (line[*i] == '\'')
		{
			*i += 1;
			break ;
		}
		len++;
		*i += 1;
	}
	return (ft_substr(line, start, len));
}

/*----------------------------------------------------------------------------*/

char	*word(char *line, int *i)
{
	int	len;
	int	start;

	len = 0;
	start = *i;
	while (line[*i])
	{
		if (len && ft_strchr("<>|$ \'\"", line[*i]))
			break ;
		len++;
		*i += 1;
	}
	return (ft_substr(line, start, len));
}
