/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:21:54 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/02 23:22:01 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

char	is_operators(char qoute, char a, char b)
{
	return ((!qoute && a == '<' && b == '<')
		|| (!qoute && a == '<' && b != '<')
		|| (!qoute && a == '>' && b == '>')
		|| (!qoute && a == '>' && b != '>')
		|| (!qoute && a == '|'));
}

/*----------------------------------------------------------------------------*/

char	get_operator(t_token **token, char *line, int *i)
{
	int	ret;

	ret = 0;
	if (line[*i] == '<' && line[*i + 1] == '<')
		ret += get_here_doc(token, i);
	else if (line[*i] == '<' && line[*i + 1] != '<')
		ret += get_red_in(token, i);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		ret += get_red_append(token, i);
	else if (line[*i] == '>' && line[*i + 1] != '>')
		ret += get_red_out(token, i);
	else if (line[*i] == '|')
		ret += get_pipe(token, i);
	return (ret);
}
