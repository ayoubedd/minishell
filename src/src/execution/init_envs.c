/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:17:59 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/07 17:31:35 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include "../../includes/builtins.h"

static void	add_back(t_exenv **head, t_exenv *node)
{
	t_exenv	*tmp;

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

t_exenv	*init_envs(t_env *env)
{
	t_exenv	*head;
	t_exenv	*node;

	head = NULL;
	if (!env)
		return (NULL);
	while (env)
	{
		node = malloc(sizeof(t_exenv));
		if (!node)
			return (NULL);
		node->key = extract_key(env->env);
		node->value = extract_value(env->env);
		node->next = NULL;
		add_back(&head, node);
		env = env->next;
	}
	return (head);
}
