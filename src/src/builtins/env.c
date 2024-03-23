/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:29:14 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/06 17:53:38 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"

void	env_blt(t_exec *exec)
{
	t_exenv	*env;

	env = exec->env;
	while (env)
	{
		if (!env->value)
		{
			env = env->next;
			continue ;
		}
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	g_exit_code = 0;
}
