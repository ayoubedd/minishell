/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 10:38:12 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/09 17:43:58 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* inert lsit of the optinals argument of the command */
void	insert_parser_opt(t_parser **parser, char *s)
{
	t_opt	*node;
	t_opt	*new;

	new = (t_opt *)malloc (sizeof(t_opt));
	node = (*parser)->cmd_option;
	new->opt = s;
	new->next = NULL;
	if ((*parser)->cmd_option == NULL)
	{
		(*parser)->cmd_option = new;
		return ;
	}
	else
		while (node != NULL && node->next != NULL)
			node = node->next;
	node->next = new;
}

/* insert parser */
void	insert_parser(t_parser **root, t_parser *parser)
{
	t_parser	*node;

	node = (*root);
	if ((*root) == NULL || root == NULL)
	{
		(*root) = parser;
		return ;
	}
	else
		while (node && node->next)
			node = node->next;
	node->next = parser;
}

void	parser_parse_lexer(t_data **lexer, t_parser **root)
{
	t_data		*tmp;
	t_parser	*parser;

	tmp = (*lexer);
	parser = init_parser();
	while (tmp)
	{
		if (parser_lexer_helper (&tmp, root, &parser) == 1)
			continue ;
		if (parser_lexer_pipe (&tmp, root, &parser) == 1)
			continue ;
		if (parser_lexer_helper2(&tmp, root, &parser) == 1)
			continue ;
		if (parser_lexer_helper5 (&tmp, root, &parser) == 1)
			continue ;
		if (parser_lexer_helper3 (&tmp, root, &parser) == 1)
			continue ;
		if (parser_lexer_helper4 (&tmp, root, &parser) == 1)
			continue ;
		insert_parser (root, parser);
		tmp = tmp->next;
	}
	return ;
}
