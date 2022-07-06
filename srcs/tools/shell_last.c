/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:57:06 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/02 23:57:08 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell	*shell_last(t_shell *shell)
{
	if (shell == NULL)
		return (NULL);
	while (shell->next)
		shell = shell->next;
	return (shell);
}
