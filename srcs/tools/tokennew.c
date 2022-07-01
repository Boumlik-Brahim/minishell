/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:33:05 by haitkadi          #+#    #+#             */
/*   Updated: 2022/03/30 20:11:39 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

t_token	*tokennew(char *content, int token)
{
	t_token	*temp;

	temp = (t_token *)malloc(sizeof(t_token));
	if (!temp)
		return (NULL);
	temp->prev = NULL;
	temp->token = token;
	temp->content = content;
	temp->next = NULL;
	return (temp);
}
