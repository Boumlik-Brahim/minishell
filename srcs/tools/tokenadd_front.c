/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenadd_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:08:41 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/03 00:08:44 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	tokenadd_front(t_token **lst, t_token *new)
{
	if (lst == NULL)
		*lst = new;
	else
	{
		(*lst)->prev = new;
		new->next = *lst;
		*lst = new;
	}
}
