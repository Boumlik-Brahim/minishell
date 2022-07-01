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

t_shell	*shell_new(int token, char *data, char **switchs, int file)
{
	t_shell	*temp;

	temp = (t_shell *)malloc(sizeof(t_shell));
	if (!temp)
		return (NULL);
	temp->prev = NULL;
	temp->token = token;
	temp->data = data;
	temp->switchs = switchs;
	temp->file = file;
	temp->next = NULL;
	return (temp);
}
