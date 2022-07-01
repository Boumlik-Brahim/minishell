/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:16:30 by haitkadi          #+#    #+#             */
/*   Updated: 2021/11/15 11:16:38 by haitkadi         ###   ########.fr       */
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
