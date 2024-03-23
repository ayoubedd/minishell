/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 20:29:16 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/07 11:18:50 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_token_type(char c)
{
	if (c == '"')
		return (7);
	else if (c == '\'')
		return (8);
	else
		return (5);
}

void	ft_malloc(char **tmp, char **val)
{
	if (tmp)
	{
		*tmp = ft_calloc(1, sizeof(char));
		(*tmp)[0] = '\0';
	}
	if (val)
	{
		*val = ft_calloc (1, sizeof(char));
		(*val)[0] = '\0';
	}
}

char	*lexer_collect2_helper(t_lexer *lexer, char c, int *n)
{
	char	*tmp;
	char	*val;
	char	*s;

	ft_malloc (NULL, &val);
	*n = 1;
	while (lexer->c != c && lexer->c != '\0')
	{
		s = lexer_get_char_as_string (lexer);
		tmp = val;
		val = ft_strjoin (tmp, s);
		free (s);
		free(tmp);
		lexer_advance(lexer);
	}
	return (val);
}

char	*lexer_collect2(t_lexer *lexer, char c)
{
	char	*val;
	int		n;

	n = 0;
	val = lexer_collect2_helper (lexer, c, &n);
	if (lexer->c == c)
		n += 1;
	if (n != 2)
	{
		free (val);
		return (NULL);
	}
	return (val);
}

char	*lexer_collect_test(t_lexer *lexer, char c)
{
	char	*val;

	lexer_advance(lexer);
	val = lexer_collect2 (lexer, c);
	if (val == NULL)
		return (NULL);
	else
		lexer->here_doc = 0;
	lexer_advance (lexer);
	return (val);
}
