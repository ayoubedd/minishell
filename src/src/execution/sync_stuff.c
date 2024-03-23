/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:01:48 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/11 19:53:15 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"

static char	*strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*str;

	len = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len += ft_strlen(s1);
	if (s2)
		len += ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	cpy_to_buffer(s1, s2, str);
	return (str);
}

static void	add_back_raw(t_env **head, t_env *node)
{
	t_env	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

static void	clean_raw_env(t_env **env)
{
	t_env	*node;
	t_env	*tmp;

	node = *env;
	while (node)
	{
		tmp = node->next;
		free(node->env);
		free(node);
		node = tmp;
	}
	*env = NULL;
}

static char	*join_key_value(char *key, char *value)
{
	char	*tmp;
	char	*key_value;

	if (!key)
		return (NULL);
	if (!value)
		return (ft_strdup(key));
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	key_value = strjoin(tmp, value);
	free(tmp);
	return (key_value);
}

void	sync_stuff(t_exec *exec, t_minshell *mini)
{
	t_exenv	*env;
	t_env	*node;

	env = exec->env;
	clean_raw_env(&mini->env);
	while (env)
	{
		node = malloc(sizeof(t_env));
		if (!node)
			return ;
		node->env = join_key_value(env->key, env->value);
		node->next = NULL;
		add_back_raw(&mini->env, node);
		env = env->next;
	}
	mini->cwd = exec->cwd;
}
