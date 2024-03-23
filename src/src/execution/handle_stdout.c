/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stdout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:07:45 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/09 17:57:00 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"

static void	open_out_files(t_list *files)
{
	int		tmp;
	t_file	*output;

	while (files)
	{
		output = files->content;
		if (output->type == DEFAULT || output->type == APPEND)
		{
			tmp = open(output->file_name, O_CREAT, 0644);
			if (tmp == -1)
			{
				files = files->next;
				continue ;
			}
			if (close(tmp) == -1)
				perror("minishell: close");
		}
		files = files->next;
	}
}

int	handle_outfile(t_list *files, t_output_type type)
{
	int		fd;
	t_file	*out_file;

	open_out_files(files);
	out_file = last_input(files);
	fd = 0;
	if (type == OUTPUT_FILE)
		fd = open(out_file->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (type == OUTPUT_FILE_APPEND)
		fd = open(out_file->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(out_file->file_name);
		return (-1);
	}
	return (fd);
}

int	handle_outpipe(t_cmd *cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	if (cmd->next->stdin == -1)
	{
		cmd->next->stdin = fd[0];
		cmd->read_pipe = fd[0];
	}
	else
	{
		if (close(fd[0]) == -1)
			perror("minishell: close");
	}
	return (fd[1]);
}

static void	next_command_input_pipe(t_cmd *cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		return ;
	}
	if (close(fd[1]) == -1)
		perror("minishell: close");
	cmd->next->stdin = fd[0];
	cmd->read_pipe = fd[0];
}

int	handle_stdout(t_cmd *cmd, t_parser *raw)
{
	t_output_type	type;

	type = output_type(raw);
	if (type == OUTPUT_STDOUT)
		return (STDOUT_FILENO);
	if (type == OUTPUT_FILE)
	{
		if (raw->parser_right == 1 && cmd->next->stdin == -1)
			next_command_input_pipe(cmd);
		return (handle_outfile(raw->file_output, OUTPUT_FILE));
	}
	if (type == OUTPUT_FILE_APPEND)
	{
		if (raw->parser_right == 1 && cmd->next->stdin == -1)
			next_command_input_pipe(cmd);
		return (handle_outfile(raw->file_output, OUTPUT_FILE_APPEND));
	}
	if (type == OUTPUT_PIPE)
		return (handle_outpipe(cmd));
	return (-1);
}
