/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_collect_id.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:58:37 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/07 18:11:30 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*lexer_collect_id3(t_lexer *lexer, char c)
{
	char	*tmp;
	char	*val;
	int		n;
	char	*s;

	n = 0;
	ft_malloc(&tmp, &val);
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
		ft_error("unixpected token\n", 9);
	lexer_advance (lexer);
	return (tmp);
}

char	*lexer_collect_id4_helper(t_lexer *lexer)
{
	char	*s;
	char	*tmp;
	char	*tmp2;

	ft_malloc (&tmp, NULL);
	while (check_case(lexer) != 1 && (lexer->c != '"' && lexer->c != '\''))
	{
		s = lexer_get_char_as_string (lexer);
		tmp2 = tmp;
		tmp = ft_strjoin (tmp2, s);
		free (tmp2);
		free (s);
		lexer_advance (lexer);
	}
	return (tmp);
}

char	*lexer_collect_id4(t_lexer *lexer)
{
	char	*tmp;

	tmp = lexer_collect_id4_helper (lexer);
	if (lexer->here_doc != 1)
		return (tmp);
	else if (lexer->here_doc == 1)
		lexer->here_doc = 0;
	return (tmp);
}

char	*lexer_collect_id_helper(t_lexer *lexer, int *check)
{
	char	*val;
	char	*tmp;
	char	*tmp2;

	ft_malloc (NULL, &val);
	if (lexer->c == '"' || lexer->c == '\'')
	{
		tmp = lexer_collect_test(lexer, lexer->c);
		if (!tmp)
			return (NULL);
		tmp2 = val;
		val = ft_strjoin (tmp2, tmp);
		free (tmp2);
		free (tmp);
		*check = 1;
	}
	else
	{
		tmp = lexer_collect_id4 (lexer);
		tmp2 = val;
		val = ft_strjoin (tmp2, tmp);
		free (tmp);
		free (tmp2);
	}
	return (val);
}

/*store the cmd or the string before the special caracter*/
t_token	*lexer_collect_id(t_lexer *lexer, int token_type)
{
	int		check;
	char	*val;
	char	*tmp;
	char	*tmp2;
	t_token	*token;

	ft_malloc (&val, NULL);
	check = 0;
	while (check_case (lexer) != 1 && lexer->c)
	{
		tmp = lexer_collect_id_helper (lexer, &check);
		if (!tmp)
			return (NULL);
		tmp2 = val;
		val = ft_strjoin (tmp2, tmp);
		free (tmp);
		free (tmp2);
		if (check_case2(lexer) == 1 && check != 0)
			break ;
		check = 0;
	}
	token = init_token(token_type, val);
	return (token);
}
