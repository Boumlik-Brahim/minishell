/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shelldelone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:03:16 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/03 00:03:18 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	void	free_2d_array(char	**arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
	}
	arr = NULL;
}

void	shelldelone(t_shell *shell)
{
	if (shell)
	{
		ft_free(shell->data);
		free_2d_array(shell->switchs);
		free(shell);
		shell = NULL;
	}
}
