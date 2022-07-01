/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:54:25 by haitkadi          #+#    #+#             */
/*   Updated: 2021/11/14 17:54:30 by haitkadi         ###   ########.fr       */
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
