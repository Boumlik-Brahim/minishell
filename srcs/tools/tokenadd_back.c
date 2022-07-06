/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenadd_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:08:16 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/03 00:08:18 by haitkadi         ###   ########.fr       */
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
		if (new->token == WORD && is_last_operator(temp) \
			&& temp->token != PIPE && !temp->content)
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
