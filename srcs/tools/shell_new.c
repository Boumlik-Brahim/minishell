/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:02:03 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/03 00:02:04 by haitkadi         ###   ########.fr       */
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
