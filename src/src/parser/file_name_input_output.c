/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name_input_output.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:46:24 by hlahrach          #+#    #+#             */
/*   Updated: 2022/08/09 15:48:14 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_file	*file_name(char *name, char *tmp1, t_data **tmp)
{
	t_file	*file;

	file = (t_file *)malloc (sizeof (t_file));
	if (!file)
		return (NULL);
	file->file_name = name;
	file->last = 0;
	if (ft_strcmp (tmp1, ">>") == 0)
		file->type = APPEND;
	else if (ft_strcmp (tmp1, ">") == 0)
		file->type = DEFAULT;
	if ((*tmp)->next == NULL || (ft_strcmp ((*tmp)->next->cmd, ">") != 0
			&& ft_strcmp((*tmp)->next->cmd, ">>") != 0))
		file->last = 1;
	return (file);
}

t_file	*file_name_input(char *name, char *tmp1, t_data **tmp)
{
	t_file	*file;

	file = (t_file *)malloc (sizeof (t_file));
	if (!file)
		return (NULL);
	file->file_name = name;
	file->last = 0;
	if (ft_strcmp (tmp1, "<<") == 0)
		file->type = HEREDOC;
	else if (ft_strcmp (tmp1, "<") == 0)
		file->type = DEFAULT;
	if ((*tmp)->next == NULL || (ft_strcmp ((*tmp)->next->cmd, "<") != 0
			&& ft_strcmp ((*tmp)->next->cmd, "<<") != 0))
		file->last = 1;
	file->token_type = (*tmp)->token_type;
	return (file);
}
