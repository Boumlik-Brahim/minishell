/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:46:31 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/02 23:46:34 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

void	handle_files(int *args, char *file, int token)
{
	if (args[0] == -1 || args[1] == -1)
		return ;
	args[2] = 0;
	if (token == RED_IN && args[0])
	{
		close(args[0]);
		args[0] = open_file(file, token);
	}
	else if (token == RED_IN && args[0] == -2)
		args[0] = open_file(file, token);
	else if ((token == RED_OUT || token == RED_APPEND) && args[1])
	{
		close(args[1]);
		args[1] = open_file(file, token);
	}
	else if ((token == RED_OUT || token == RED_APPEND) && args[1] == -2)
		args[1] = open_file(file, token);
}

/*----------------------------------------------------------------------------*/

char	filetype(char *input)
{
	struct stat	file_stat;

	if (stat(input, &file_stat))
		return (0);
	if (!S_ISREG(file_stat.st_mode) && S_ISDIR(file_stat.st_mode))
	{
		put_error(input, "Is a directory", 126);
		return (1);
	}
	return (0);
}

/*----------------------------------------------------------------------------*/

void	check_file_permession(char *file, int macro)
{
	if (!filetype(file))
	{
		if (macro == RED_IN)
		{
			if (access(file, F_OK) != 0)
				put_error(file, "No such file of directory", 1);
			else if (access(file, R_OK) != 0)
				put_error(file, "Permission denied", 1);
		}
		else if (macro == RED_OUT || macro == RED_APPEND)
			if (access(file, W_OK) != 0)
				put_error(file, "Permission denied", 1);
	}
}

/*----------------------------------------------------------------------------*/

int	open_file(char *filename, int macro)
{
	int	file;
	int	type;

	file = -1;
	type = -1;
	if (macro == RED_IN)
	{
		file = open(filename, O_RDONLY);
		type = RED_IN;
	}
	else if (macro == RED_OUT)
	{
		file = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		type = RED_OUT;
	}
	else if (macro == RED_APPEND)
	{
		file = open(filename, O_CREAT | O_RDWR | O_APPEND, 0777);
		type = RED_APPEND;
	}
	if (type && file < 0)
		check_file_permession(filename, type);
	return (file);
}
