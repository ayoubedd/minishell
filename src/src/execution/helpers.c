/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:20:06 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/06 17:46:31 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/builtins.h"

t_builtin	which_builtin(t_parser *list)
{
	size_t	i;
	char	*cmds[8];

	i = 0;
	if (!list->cmd)
		return (NON);
	cmds[0] = "echo";
	cmds[1] = "cd";
	cmds[2] = "pwd";
	cmds[3] = "export";
	cmds[4] = "unset";
	cmds[5] = "env";
	cmds[6] = "exit";
	cmds[7] = NULL;
	while (cmds[i])
	{
		if (ft_strcmp(cmds[i], list->cmd) == 0)
			return (i + 1);
		i++;
	}
	return (NON);
}

static size_t	cmds_count(t_parser *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_exmode	exec_mode(t_parser *raw)
{
	size_t	i;
	size_t	count;
	char	*cmds[8];

	i = 0;
	cmds[0] = "echo";
	cmds[1] = "cd";
	cmds[2] = "pwd";
	cmds[3] = "export";
	cmds[4] = "unset";
	cmds[5] = "env";
	cmds[6] = "exit";
	cmds[7] = NULL;
	count = cmds_count(raw);
	if (count == 1 && which_builtin(raw) == EXIT && raw->file_output)
		return (NORMAL);
	if (count > 1 || raw->file_output)
		return (EMBEDDED);
	while (raw->cmd && cmds[i])
	{
		if (!ft_strcmp(raw->cmd, cmds[i]))
			return (NORMAL);
		i++;
	}
	return (EMBEDDED);
}

void	cleanup_close_pipes(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->stdin != -1 && cmd->stdin != STDIN_FILENO)
		{
			if (close(cmd->stdin) == -1)
				perror("minishell: close");
		}
		if (cmd->stdout != -1 && cmd->stdout != STDOUT_FILENO)
		{
			if (close(cmd->stdout) == -1)
				perror("minishell: close");
		}
		if (cmd->doc_write_fd != -1)
		{
			if (close(cmd->doc_write_fd) == -1)
				perror("minishell: close");
		}
		cmd = cmd->next;
	}
}

void	kill_children(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pid > 0)
			kill(cmd->pid, SIGKILL);
		cmd = cmd->next;
	}
}
