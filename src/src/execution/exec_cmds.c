/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:36:50 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/12 19:24:32 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include "../../includes/builtins.h"

static void	close_pipes(t_cmd *cmd, t_bool close_read)
{
	if (cmd->stdin != STDIN_FILENO)
	{
		if (close(cmd->stdin))
			perror("minishell: close dd");
		cmd->stdin = -1;
	}
	if (cmd->stdout != STDOUT_FILENO)
	{
		if (close(cmd->stdout))
			perror("minishell: close bb");
		cmd->stdout = -1;
	}
	if (close_read && cmd->read_pipe != -1)
	{
		if (close(cmd->read_pipe) == -1)
			perror("minishell: close");
		cmd->read_pipe = -1;
	}
	if (cmd->doc_write_fd != -1)
	{
		if (close(cmd->doc_write_fd) == -1)
			perror("minishell: close");
		cmd->doc_write_fd = -1;
	}
}

static void	dup_pipes(t_cmd *cmd)
{
	if (dup2(cmd->stdin, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(cmd->stdout, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		exit(EXIT_FAILURE);
	}
}

static void	exec_cmd(t_exec *exec, t_cmd *cmd, t_parser *raw)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return ;
	}
	if (pid == 0)
	{
		dup_pipes(cmd);
		close_pipes(cmd, TRUE);
		signal(SIGQUIT, SIG_DFL);
		if (cmd->builtin)
			exec_blt(exec, cmd, raw, EMBEDDED);
		else
			execve(cmd->path, cmd->args, cmd->env);
		perror("minishell: execve");
		exit(EXIT_FAILURE);
	}
	cmd->pid = pid;
	close_pipes(cmd, FALSE);
}

static void	continue_up(t_cmd **cmd, t_parser **raw)
{
	*cmd = (*cmd)->next;
	*raw = (*raw)->next;
}

t_bool	exec_cmds(t_exec *exec)
{
	t_cmd		*cmd;
	t_parser	*raw;
	t_bool		status;

	cmd = exec->cmd;
	raw = exec->raw;
	while (cmd && raw)
	{
		cmd->stdin = handle_stdin(cmd, raw);
		cmd->stdout = handle_stdout(cmd, raw);
		if (cmd->stdin == -1 || cmd->stdout == -1)
			return (TRUE);
		if (cmd->skip == TRUE)
		{
			close_pipes(cmd, FALSE);
			if (!cmd->next)
				status = TRUE;
			continue_up(&cmd, &raw);
			continue ;
		}
		status = FALSE;
		exec_cmd(exec, cmd, raw);
		continue_up(&cmd, &raw);
	}
	return (status);
}
