/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:21:13 by hlahrach          #+#    #+#             */
/*   Updated: 2022/08/30 14:58:36 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_token_is_word(t_token_type token_type)
{
	if (token_type == TOKEN_ID || token_type == TOKEN_D_QOTES
		|| token_type == TOKEN_S_QOTES || token_type == TOKEN_FLAGE)
	{
		return (1);
	}
	return (0);
}

int	check_special(int token_type)
{
	if (token_type == TOKEN_APPEND || token_type == TOKEN_INPUT
		|| token_type == TOKEN_OUTPUT || token_type == TOKEN_HERDOC)
		return (0);
	return (1);
}

int	check_error_pipe(t_data *prev, t_data *node)
{
	if (prev == NULL)
		return (0);
	if (node->next == NULL)
		return (0);
	if (check_token_is_word (prev->token_type) == 0)
		return (0);
	return (1);
}

int	check_error_redirection(t_data *node)
{
	if (!node->next)
		return (0);
	if (node->next && check_token_is_word (node->next->token_type) == 0)
		return (0);
	return (1);
}

int	syntax_error(t_data **lexer)
{
	t_data	*node;
	t_data	*prev;

	prev = NULL;
	node = (*lexer);
	while (node != NULL)
	{
		if (node->token_type == TOKEN_PIPE)
			if (check_error_pipe (prev, node) == 0)
				return (0);
		if (check_special(node->token_type) == 0)
		{
			if (check_error_redirection (node) == 0)
				return (0);
		}
		prev = node;
		node = node->next;
	}
	return (1);
}
