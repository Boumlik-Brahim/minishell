/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:04:04 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/03 00:04:05 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	token_clear(t_token **lst)
{
	t_token	*head;
	t_token	*current;

	if (!*lst)
		return ;
	head = *lst;
	*lst = NULL;
	while (head != NULL)
	{
		current = head;
		head = head->next;
		tokendelone(current);
	}
}
