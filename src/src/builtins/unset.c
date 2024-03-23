/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:50:56 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/13 00:21:50 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include "../../includes/builtins.h"

static void	unset_var(t_exenv *env, char *key)
{
	t_exenv	*prev;

	prev = NULL;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			if (prev)
				prev->next = env->next;
			free(env->key);
			free(env->value);
			free(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

void	unset_blt(t_exec *exec, t_cmd *cmd)
{
	t_bool	error;
	size_t	i;

	i = 1;
	error = FALSE;
	while (cmd->args[i])
	{
		if (valid_key_check(cmd->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(cmd->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			i++;
			error = TRUE;
			continue ;
		}
		unset_var(exec->env, cmd->args[i]);
		i++;
	}
	if (error == TRUE)
		g_exit_code = 1;
	else
		g_exit_code = 0;
}
