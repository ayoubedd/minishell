/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:05:09 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/08 14:20:03 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include "../../includes/builtins.h"
#include <sys/stat.h>

static t_bool	check_input_files(t_parser *raw, t_cmd *cmd)
{
	t_file	*input;
	t_list	*list;
	t_bool	status;

	status = FALSE;
	while (raw)
	{
		list = raw->file_input;
		while (list)
		{
			input = list->content;
			if (input->type == DEFAULT)
			{
				if (!check_file_exist(input))
				{
					cmd->skip = TRUE;
					status = TRUE;
				}
			}
			list = list->next;
		}
		raw = raw->next;
	}
	return (status);
}

static t_bool	check_cmds_path(t_parser *raw, t_cmd *cmd)
{
	t_bool	status;

	status = FALSE;
	while (raw && cmd)
	{
		if (cmd->builtin != NON || !raw->cmd)
		{
			if (!raw->cmd)
				cmd->skip = TRUE;
			cmd = cmd->next;
			raw = raw->next;
			continue ;
		}
		if (access(cmd->path, F_OK))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(raw->cmd, STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			cmd->skip = TRUE;
			status = TRUE;
		}
		cmd = cmd->next;
		raw = raw->next;
	}
	return (status);
}

static t_bool	check_cmds_permissions(t_cmd *cmd)
{
	t_bool	status;

	status = FALSE;
	while (cmd)
	{
		if (cmd->builtin != NON || !cmd->path)
		{
			cmd = cmd->next;
			continue ;
		}
		if (access(cmd->path, X_OK))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->path, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			cmd->skip = TRUE;
			status = TRUE;
		}
		cmd = cmd->next;
	}
	return (status);
}

static t_bool	check_cmd_not_dir(t_cmd *cmd)
{
	t_bool		status;
	struct stat	file;

	status = FALSE;
	while (cmd)
	{
		stat(cmd->path, &file);
		if (S_ISDIR(file.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->path, STDERR_FILENO);
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			cmd->skip = TRUE;
			status = TRUE;
		}
		cmd = cmd->next;
	}
	return (status);
}

void	checker(t_exec *exec)
{
	if (check_input_files(exec->raw, exec->cmd))
	{
		g_exit_code = 1;
		return ;
	}
	if (check_cmds_path(exec->raw, exec->cmd))
	{
		g_exit_code = 127;
		return ;
	}
	if (check_cmds_permissions(exec->cmd))
	{
		g_exit_code = 126;
		return ;
	}
	if (check_cmd_not_dir(exec->cmd))
	{
		g_exit_code = 126;
		return ;
	}
}
