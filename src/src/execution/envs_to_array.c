/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:34:58 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/07 17:21:01 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	cpy_to_buffer(char *s1, char *s2, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	if (s2)
	{
		while (s2[j])
		{
			str[i + j] = s2[j];
			j++;
		}
	}
	str[i + j] = '\0';
}

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

static size_t	envs_count(t_exenv *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**envs_to_array(t_exenv *env)
{
	char	**envs;
	char	*tmp;
	size_t	count;
	size_t	i;

	i = 0;
	if (!env)
		return (NULL);
	count = envs_count(env);
	envs = (char **)malloc((count + 1) * sizeof(char *));
	if (!envs)
		return (NULL);
	while (env)
	{
		tmp = strjoin(env->key, "=");
		envs[i] = strjoin(tmp, env->value);
		free(tmp);
		i++;
		env = env->next;
	}
	envs[i] = NULL;
	return (envs);
}
