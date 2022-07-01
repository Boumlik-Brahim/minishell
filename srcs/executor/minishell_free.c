/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:49:19 by bbrahim           #+#    #+#             */
/*   Updated: 2022/06/30 11:00:33 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_free_env(t_env *head, char error)
{
	t_env	*tmp;

	if (head)
	{
		while (head)
		{
			tmp = head;
			head = head->next;
			if (tmp->key)
				free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			if (tmp)
				free(tmp);
		}
	}
	if (error)
		ft_putstr_fd("\033[1;31mAllocation failed\033[0m\n", 2);
}

/* -------------------------------------------------------------------------- */