/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:03:14 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/05 14:18:06 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"

t_file	*last_input(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list->content);
}

t_output_type	output_type(t_parser *cmd)
{
	t_file	*output;

	output = last_input(cmd->file_output);
	if (!output && cmd->parser_right == 1)
		return (OUTPUT_PIPE);
	if (!output && cmd->parser_right == 0)
		return (OUTPUT_STDOUT);
	if (output->type == APPEND)
		return (OUTPUT_FILE_APPEND);
	return (OUTPUT_FILE);
}

t_bool	is_last_heredoc(t_list *list)
{
	t_file	*file;

	while (list)
	{
		file = list->content;
		if (file->type == HEREDOC)
			return (FALSE);
		list = list->next;
	}
	return (TRUE);
}
