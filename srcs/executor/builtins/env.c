/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:21:15 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/05 20:07:27 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/* -------------------------------------------------------------------------- */

char	**ft_env_table(t_env *env)
{
	char	**res;
	char	*tmp;
	int		lstsize;
	t_env	*current;
	int		i;

	lstsize = ft_env_size(env);
	res = (char **)malloc(sizeof(char *) * (lstsize + 1));
	if (!res)
		return (NULL);
	i = -1;
	current = env;
	while (++i < lstsize)
	{
		tmp = ft_strjoin(current->key, "=");
		res[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		current = current->next;
	}
	res[i] = NULL;
	return (res);
}

/* -------------------------------------------------------------------------- */

void	ft_env_shlvl(t_env *env, char operator)
{
	t_env	*current;
	char	*value;
	int		val;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "SHLVL") == 0)
		{
			val = ft_atoi(current->value);
			if (operator == '+')
				val++;
			else if (operator == '-' && val > 0)
					val--;
			free(current->value);
			value = ft_itoa(val);
			current->value = ft_strdup(value);
			free(value);
		}
		current = current->next;
	}
}

/* -------------------------------------------------------------------------- */

void	ft_empty_env(t_env **env)
{
	char	*pwdval;
	char	cwd[PATH_MAX];

	pwdval = getcwd(cwd, PATH_MAX);
	ft_envadd_back(env, ft_envnew(ft_strdup("OLDPWD"), ft_strdup(""), 0));
	ft_envadd_back(env, ft_envnew(ft_strdup("PATH"),
			ft_strdup(_PATH_STDPATH), 0));
	ft_envadd_back(env, ft_envnew(ft_strdup("PWD"), ft_strdup(pwdval), 1));
	ft_envadd_back(env, ft_envnew(ft_strdup("SHLVL"), ft_strdup("1"), 1));
	ft_envadd_back(env, ft_envnew(ft_strdup("_"),
			ft_strdup("/usr/bin/env"), 1));
}

/* -------------------------------------------------------------------------- */

int	ft_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (g_state.empty_env == true)
		{
			if (ft_strcmp(current->key, "PATH") && current->print == 1
				&& current->value)
			{
				printf("%s=%s\n", current->key, current->value);
			}
		}
		else if (current->print == 1 && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (g_state.exit_state);
}

/* -------------------------------------------------------------------------- */