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

char	tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (new == NULL)
		return (1);
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = tokenlast(*lst);
		if (is_last_operator(temp) && temp->token != PIPE && !temp->content)
		{
			temp->content = ft_strdup(new->content);
			tokendelone(new);
		}
		else
		{
			temp->next = new;
			new->prev = temp;
		}
	}
	return (0);
}
