/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shelladd_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:03:01 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/03 00:03:03 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	shelladd_front(t_shell **shell, t_shell *new)
{
	if (!new)
		return (1);
	if (shell == NULL)
		*shell = new;
	else
	{
		(*shell)->prev = new;
		new->next = *shell;
		*shell = new;
	}
	return (0);
}
