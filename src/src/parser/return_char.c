/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:08:22 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/07 11:20:10 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*return_char_helper(t_lexer *lexer)
{
	char	*tmp;
	char	*tmp2;
	char	*val;

	ft_malloc (NULL, &val);
	while (check_case(lexer) != 1)
	{
		if (lexer->c == '"' || lexer->c == '\'')
			return (val);
		tmp = lexer_get_char_as_string (lexer);
		tmp2 = val;
		val = ft_strjoin (tmp2, tmp);
		free (tmp);
		free (tmp2);
		lexer_advance (lexer);
	}
	if (!val)
		return (NULL);
	return (val);
}

/* merge the old string with the new characters */
char	*return_char(t_lexer *lexer)
{
	char	*val;
	char	*tmp;
	char	*tmp2;

	if (lexer->c == '"' || lexer->c == '\'')
	{
		ft_malloc (NULL, &val);
		tmp = lexer_collect_test (lexer, lexer->c);
		if (!tmp)
		{
			free (val);
			return (NULL);
		}
		tmp2 = val;
		val = ft_strjoin (tmp2, tmp);
		free (tmp2);
		free (tmp);
		return (val);
	}
	else
		tmp = return_char_helper (lexer);
	return (tmp);
}
