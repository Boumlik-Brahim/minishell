/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_qoutes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:18:57 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/02 23:19:04 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

char	check_qoutes(char *line)
{
	int		i;
	char	dbl;
	char	sngl;

	dbl = 0;
	sngl = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' && !sngl)
			dbl = !dbl;
		else if (line[i] == '\'' && !dbl)
			sngl = !sngl;
		i++;
	}
	if (dbl || sngl)
		return (put_error("qoutes", "Syntax error", 258), 1);
	return (0);
}
