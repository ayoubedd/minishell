/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:11:10 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/12 15:43:04 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include "../../includes/builtins.h"

static void	wait_children(t_exec *exec, t_bool catch)
{
	int		tmp;
	t_cmd	*cmd;

	cmd = exec->cmd;
	while (cmd)
	{
		if (cmd->pid != -1)
			waitpid(cmd->pid, &tmp, 0);
		cmd = cmd->next;
	}
	if (catch)
	{
		if (g_exit_code == 130 && !exec->cmd->next)
			return ;
		g_exit_code = WEXITSTATUS(tmp);
	}
}

static t_exec	*init(t_minshell *mini)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->raw = mini->parser;
	exec->cwd = mini->cwd;
	exec->env = init_envs(mini->env);
	exec->env_arr = envs_to_array(exec->env);
	exec->cmd = init_cmds(exec);
	g_exit_code = 0;
	return (exec);
}

void	executor(t_minshell *mini)
{
	t_exmode	mode;
	t_exec		*exec;

	if (!mini->parser)
		return ;
	exec = init(mini);
	if (!exec)
		return ;
	if (handle_heredocs(exec->cmd, &mini->env, mini->parser))
		return (cleanup(exec));
	checker(exec);
	mode = exec_mode(exec->raw);
	if (mode == NORMAL)
		exec_blt(exec, exec->cmd, exec->raw, NORMAL);
	else
	{
		if (exec_cmds(exec))
			wait_children(exec, FALSE);
		else
			wait_children(exec, TRUE);
	}
	sync_stuff(exec, mini);
	cleanup(exec);
}
