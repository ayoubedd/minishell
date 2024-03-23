/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:27:22 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/08 17:23:12 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"

t_exenv	*find_item(t_exenv *env, char *key)
{
	if (!env || !key)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*extract_key(char *str)
{
	char	*key;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	key = ft_substr(str, 0, i);
	return (key);
}

char	*extract_value(char *str)
{
	char	*val;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (NULL);
	if (str[i] == '=' && str[i + 1] == '\0')
		return (ft_strdup(""));
	val = ft_substr(&str[i + 1], 0, ft_strlen(&str[i + 1]));
	return (val);
}

void	exenv_add_back(t_exenv **env, t_exenv *node)
{
	t_exenv	*tmp;

	tmp = *env;
	if (!tmp)
	{
		*env = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	exenv_insert_var(t_exenv **env, char *key, char *val)
{
	t_exenv	*tmp;

	if (!key || !val)
		return ;
	tmp = find_item(*env, key);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(val);
	}
	else
	{
		tmp = malloc(sizeof(t_exenv));
		if (!tmp)
			return ;
		tmp->key = ft_strdup(key);
		tmp->value = ft_strdup(val);
		tmp->next = NULL;
		exenv_add_back(env, tmp);
	}
}
