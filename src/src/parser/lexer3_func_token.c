/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3_func_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:46:42 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/07 18:12:49 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*lexer_collect_id2(t_lexer *lexer, char c)
{
	char	*tmp;
	char	*val;
	int		n;
	char	*s;

	n = 0;
	ft_malloc (&tmp, &val);
	n += 1;
	lexer_advance(lexer);
	while (lexer->c != c && lexer->c != '\0')
	{
		s = lexer_get_char_as_string (lexer);
		tmp = ft_strjoin (tmp, s);
		free (s);
		lexer_advance(lexer);
	}
	if (lexer->c == c)
		n += 1;
	if (n != 2)
		ft_error ("unixpected token\n", 8);
	lexer_advance (lexer);
	return (tmp);
}

int	lexer_base_case(t_lexer *data, t_data **node, t_token *token)
{
	if ((data->c == '"' || data->c == '\'') && data->index != 0)
	{
		if ((data->index != 0 && data->cmd[data->index - 1] == ' ')
			|| data->index == 0)
		{
			if (data->c == '"')
				token = lexer_collect_string(data,
						TOKEN_D_QOTES, data->c);
			else if (data->c == '\'')
				token = lexer_collect_string(data,
						TOKEN_S_QOTES, data->c);
			if (token == NULL)
				return (2);
			insert_lexer(node, token);
			return (0);
		}
	}
	return (1);
}

int	lexer_func_check_token(t_lexer *data, t_data **node)
{
	if (data->c == '<' && data->cmd[data->index + 1] == '<')
	{
		lexer_advance(data);
		insert_lexer(node, lexer_collect_special(data, TOKEN_HERDOC));
		data->here_doc = 1;
		return (1);
	}
	else if (data->c == '>' && data->cmd[data->index + 1] == '>')
	{
		lexer_advance(data);
		insert_lexer(node, lexer_collect_special(data, TOKEN_APPEND));
		return (2);
	}
	else if (data->c == '<' && data->cmd[data->index + 1] != '<')
	{
		insert_lexer(node, lexer_collect_special(data, TOKEN_INPUT));
		return (3);
	}
	else if (data->c == '>' && data->cmd[data->index + 1] != '>')
	{
		insert_lexer(node, lexer_collect_special(data, TOKEN_OUTPUT));
		return (4);
	}
	return (0);
}

int	lexer_func_check_token2(t_lexer *data, t_data **node, t_token *token)
{
	if (data->c == '|')
	{
		insert_lexer(node, lexer_collect_special(data, TOKEN_PIPE));
		return (5);
	}
	else if (data->c == '-')
	{
		if (data->cmd[data->index - 1] != ' ')
			return (ft_error("command not found : \n", 5));
		insert_lexer(node, lexer_collect_special(data, TOKEN_FLAGE));
		return (2);
	}
	else
	{
		token = lexer_collect_id(data, TOKEN_ID);
		if (!token)
			return (1);
		insert_lexer(node, token);
		return (3);
	}
	return (0);
}
