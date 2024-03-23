/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stdin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:06:11 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/08 13:32:27 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"

t_input_type	input_type(t_parser *raw)
{
	t_file	*input;

	if (!raw->file_input && raw->parsre_left == 0)
		return (INPUT_STD);
	if (!raw->file_input && raw->parsre_left == 1)
		return (INPUT_PIPE);
	input = last_input(raw->file_input);
	if (input->type == DEFAULT)
		return (INPUT_FILE);
	if (input->type == HEREDOC)
		return (INPUT_HEREDOC);
	return (-1);
}

static int	handle_input_file(t_list *list)
{
	int		fd;
	t_file	*input_file;

	input_file = last_input(list);
	if (!input_file)
		return (-1);
	fd = open(input_file->file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(input_file->file_name);
	}
	return (fd);
}

int	handle_stdin(t_cmd *cmd, t_parser *raw)
{
	t_input_type	type;	

	type = input_type(raw);
	if (type == INPUT_STD)
		return (STDIN_FILENO);
	if (type == INPUT_PIPE)
		return (cmd->stdin);
	if (type == INPUT_FILE)
		return (handle_input_file(raw->file_input));
	if (type == INPUT_HEREDOC)
		return (cmd->stdin);
	return (-1);
}
