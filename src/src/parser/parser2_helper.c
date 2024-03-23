/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 20:00:23 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/12 21:54:01 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser_lexer_helper3(t_data **tmp, t_parser **root, t_parser **parser)
{
	char	*tmp2;

	tmp2 = (*tmp)->cmd;
	if ((ft_strcmp ((*tmp)->cmd, ">") == 0
			|| ft_strcmp ((*tmp)->cmd, ">>") == 0)
		&& (*tmp)->next != NULL)
	{
		(*tmp) = (*tmp)->next;
		ft_lstadd_back(&(*parser)->file_output,
			ft_lstnew(file_name((*tmp)->cmd, tmp2, tmp)));
		(*tmp) = (*tmp)->next;
		if (*tmp == NULL)
			insert_parser (root, *parser);
		return (1);
	}
	return (0);
}

int	parser_lexer_helper2(t_data **tmp, t_parser **root, t_parser **parser)
{
	if ((*parser)->cmd == NULL && check_tokentype ((*tmp)->token_type))
	{
		(*parser)->cmd = (*tmp)->cmd;
		*tmp = (*tmp)->next;
		if (*tmp == NULL)
			insert_parser (root, *parser);
		return (1);
	}
	return (0);
}

int	parser_lexer_helper5(t_data **tmp, t_parser **root, t_parser **parser)
{
	int	n;

	n = 0;
	if ((*parser)->cmd_option == NULL
		&& check_tokentype ((*tmp)->token_type))
	{
		while (*tmp != NULL && check_tokentype ((*tmp)->token_type))
		{
			insert_parser_opt (parser, (*tmp)->cmd);
			*tmp = (*tmp)->next;
			n++;
		}
		if (n == 0)
			*tmp = (*tmp)->next;
		if (*tmp == NULL)
			insert_parser (root, *parser);
		return (1);
	}
	return (0);
}

int	parser_lexer_helper4(t_data **tmp, t_parser **root, t_parser **parser)
{
	char	*tmp2;

	tmp2 = (*tmp)->cmd;
	if (ft_strcmp ((*tmp)->cmd, "<") == 0 && (*tmp)->next != NULL)
	{
		*tmp = (*tmp)->next;
		ft_lstadd_back(&(*parser)->file_input,
			ft_lstnew (file_name_input((*tmp)->cmd, tmp2, tmp)));
		(*tmp) = (*tmp)->next;
		if (*tmp == NULL)
			insert_parser (root, *parser);
		return (1);
	}
	return (0);
}
