/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_collect_special.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:17:25 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/05 14:31:23 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*collect_check(t_lexer *lexer, int token_type)
{
	char	*tmp2;
	char	*tmp;
	char	*s;
	t_token	*token;

	s = ft_calloc (1, sizeof(char));
	s[0] = '\0';
	while (check_case (lexer) != 1)
	{
		tmp = s;
		tmp2 = lexer_get_char_as_string(lexer);
		s = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		lexer_advance(lexer);
	}
	token = init_token(token_type, s);
	return (token);
}

/*collect the chareacters before the special character*/
t_token	*lexer_collect_special(t_lexer *lexer, int token_type)
{
	char	*s;
	t_token	*token;

	if (token_type == 3)
	{
		return (lexer_advance_withe_token(lexer,
				init_token(token_type, ft_strdup("<<"))));
	}
	else if (token_type == 4)
	{
		return (lexer_advance_withe_token(lexer,
				init_token(token_type, ft_strdup(">>"))));
	}
	else if (token_type == TOKEN_FLAGE)
		return (collect_check (lexer, token_type));
	s = lexer_get_char_as_string(lexer);
	token = init_token(token_type, s);
	lexer_advance (lexer);
	return (token);
}
