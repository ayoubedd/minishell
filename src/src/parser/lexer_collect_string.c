/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_collect_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:33:42 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/07 11:22:26 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer_collect_string_helper(t_lexer *lexer, char **val)
{	
	char	*tmp;

	if (lexer->c == '"')
	{
		tmp = lexer_collect_id2 (lexer, lexer->c);
		*val = ft_strjoin (*val, tmp);
	}
	else if (lexer->c == '\'')
	{
		tmp = lexer_collect_id3 (lexer, lexer->c);
		*val = ft_strjoin (*val, tmp);
	}
}

char	*lexer_collect_string_helper2(t_lexer *lexer)
{
	char	*val;
	char	*tmp;
	char	*tmp2;

	ft_malloc(NULL, &val);
	while (check_case (lexer) != 1 && lexer->c)
	{
		tmp = return_char (lexer);
		if (!tmp)
		{
			free (val);
			return (NULL);
		}
		tmp2 = val;
		val = ft_strjoin (tmp2, tmp);
		free (tmp);
		free (tmp2);
		if (check_case2(lexer) == 1)
			break ;
	}
	return (val);
}

t_token	*lexer_collect_string(t_lexer *lexer,
		int token_type, char c)
{
	char	*val;

	(void)c;
	val = lexer_collect_string_helper2 (lexer);
	if (val == NULL)
		return (NULL);
	lexer_collect_string_helper (lexer, &val);
	return (init_token(token_type, val));
}
