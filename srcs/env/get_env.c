#include"../../minishell.h"

int	ft_env_size(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!new)
	{
		ft_free_env(*lst, 1);
		exit(-1);
	}
	tmp = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*ft_envnew(char *key, char *value, bool print)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
		return (NULL);
	tmp->key = key;
	tmp->value = value;
	tmp->print = print;
	tmp->next = NULL;
	return (tmp);
}

void	ft_create_env(t_env **list, char **env)
{
	char	*value;
	char	*key;
	int		i;

	i = 0;
	*list = NULL;
	key = NULL;
	value = NULL;
	if (env[0] == NULL)
	{
		g_state.empty_env = true;
		ft_empty_env(list);
		return ;
	}
	while (env[i])
	{
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		ft_bzero(ft_strchr(env[i], '='), 1);
		key = ft_strdup(env[i]);
		ft_envadd_back(list, ft_envnew(key, value, 1));
		i++;
	}
}

char	*ft_getenv(t_env *env, char *buffer)
{
	t_env	*tmp;

	if (!env || !buffer)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(buffer, tmp->key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_keys(char *str, int c)
{
	char	*h;
	char	a;
	int		j;

	h = (char *)str;
	j = 0;
	a = (char) c;
	while (h[j] != a)
		j++;
	if (h[j] + 2 == 0)
		return (str);
	else
	{
		h[j] = 0;
		return (h);
	}
	return (0);
}
