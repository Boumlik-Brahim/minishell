/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:44:29 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/04 13:27:48 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------------------------------------------------------------- */

void	ft_handle_errorcd(char *cmd, char *arg, char *error)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd("", 2);
}

/* -------------------------------------------------------------------------- */

void	ft_handle_error(char *cmd, char *arg, char *error)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("':", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd("", 2);
}

/* -------------------------------------------------------------------------- */