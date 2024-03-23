/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 22:54:56 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/07 10:28:49 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"

static void	clean_args(char **args)
{
	size_t	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static void	clean_cmds(t_cmd *cmd)
{
	t_cmd	*next;

	if (!cmd)
		return ;
	while (cmd)
	{
		next = cmd->next;
		if (cmd->path)
			free(cmd->path);
		if (cmd->args)
			clean_args(cmd->args);
		free(cmd);
		cmd = next;
	}
}

static void	clean_env(t_exenv *env)
{
	t_exenv	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

static void	clean_env_arr(char **env)
{
	size_t	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	cleanup(t_exec *exec)
{
	clean_env(exec->env);
	clean_env_arr(exec->env_arr);
	kill_children(exec->cmd);
	cleanup_close_pipes(exec->cmd);
	clean_cmds(exec->cmd);
	free(exec);
}
