/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shelladd_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:02:45 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/03 00:02:47 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	shelladd_back(t_shell **shell, t_shell *new)
{
	t_shell	*temp;

	if (new == NULL)
		return (1);
	if (*shell == NULL)
		*shell = new;
	else
	{
		temp = shell_last(*shell);
		if (temp)
		{
			temp->next = new;
			new->prev = temp;
		}
	}
	return (0);
}
