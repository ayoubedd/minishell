/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 20:00:30 by hlahrach          #+#    #+#             */
/*   Updated: 2022/07/23 20:00:32 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/* insert parser struct to NULL */
void	parser_defaulth(t_parser *parser)
{
	parser->cmd = NULL;
	parser->cmd_option = NULL;
	parser->file_input = NULL;
	parser->file_output = NULL;
	parser->parsre_left = 0;
	parser->parser_right = 0;
	return ;
}

/* inisalze parser strcut */
t_parser	*init_parser(void)
{
	t_parser	*parser;

	parser = ft_calloc (1, sizeof (t_parser));
	if (parser == NULL)
		return (NULL);
	parser_defaulth (parser);
	return (parser);
}

/* base case to check token */
int	check_token(char *s)
{
	if (ft_strcmp (s, ">") && ft_strcmp (s, "<") && ft_strcmp (s, "<<")
		&& ft_strcmp (s, ">>") && ft_strcmp (s, "|"))
		return (1);
	return (0);
}

int	check_tokentype(int token_type)
{
	if (token_type == 1 || token_type == 2
		|| token_type == 3 || token_type == 4 || token_type == 0)
		return (0);
	return (1);
}
