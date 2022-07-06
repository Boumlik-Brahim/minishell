/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:56:48 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/03 00:03:42 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	shell_clear(t_shell **shell)
{
	t_shell	*head;
	t_shell	*current;

	if (!*shell)
		return ;
	head = *shell;
	*shell = NULL;
	while (head != NULL)
	{
		current = head;
		head = head->next;
		shelldelone(current);
	}
}
