/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:26:14 by haitkadi          #+#    #+#             */
/*   Updated: 2022/03/30 20:15:41 by haitkadi         ###   ########.fr       */
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
