/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:18:53 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/09 17:42:59 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser_lexer_helper(t_data **tmp, t_parser **root, t_parser **parser)
{
	char		*tmp2;

	tmp2 = (*tmp)->cmd;
	if (ft_strcmp ((*tmp)->cmd, "<<") == 0 && (*tmp)->next != NULL
		&& (*tmp)->token_type == 3)
	{
		*tmp = (*tmp)->next;
		ft_lstadd_back(&(*parser)->file_input,
			ft_lstnew(file_name_input((*tmp)->cmd, tmp2, tmp)));
		(*tmp) = (*tmp)->next;
		if (*tmp == NULL)
			insert_parser (root, *parser);
		return (1);
	}
	return (0);
}

int	parser_lexer_pipe(t_data **tmp, t_parser **root, t_parser **parser)
{
	t_parser	*tmp_parser;

	if (ft_strcmp ((*tmp)->cmd, "|") == 0 && (*tmp)->token_type == 0)
	{
		(*parser)->parser_right = 1;
		tmp_parser = *parser;
		insert_parser(root, tmp_parser);
		(*parser) = init_parser();
		(*parser)->parsre_left = 1;
		(*tmp) = (*tmp)->next;
		return (1);
	}
	return (0);
}
