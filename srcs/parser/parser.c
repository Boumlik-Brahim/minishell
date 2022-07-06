/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:48:21 by haitkadi          #+#    #+#             */
/*   Updated: 2022/07/06 16:15:54 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

void	print_node(t_shell *shell)
{
	int	i;

	if (shell)
	{
		while (shell)
		{
			printf("\n================Start======================\n");
			printf("| prev:%p:\n", shell->prev);
			printf("| token:%d:\n", shell->token);
			printf("| data:%s:\n", shell->data);
			if (shell->switchs)
			{
				i = 0;
				while (shell->switchs[i])
					printf("| switchs:%s:\n", shell->switchs[i++]);
			}
			printf("| fd:%d:\n", shell->file);
			printf("| next:%p:\n", shell->next);
			shell = shell->next;
			printf("=================End=======================\n");
		}
	}
}

/*----------------------------------------------------------------------------*/

void	parser(char *line, t_env **env)
{
	t_token	*token;
	t_shell	*shell;
	t_data	data;

	shell = NULL;
	token = lexer(line, *env);
	if (!token)
		return ;
	if (process_data(&shell, token, *env))
		return ;
	token_clear(&token);
	ft_ms_backbone(env, shell, &data);
	shell_clear(&shell);
}
