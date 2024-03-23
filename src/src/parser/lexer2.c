/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:02:04 by hlahrach          #+#    #+#             */
/*   Updated: 2022/07/20 13:03:16 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*init lexer ==> initilize the lexer from  the line input */
t_lexer	*init_lexer(char *line)
{
	t_lexer	*data;

	if (line == NULL)
		return (NULL);
	data = ft_calloc(1, sizeof(t_lexer));
	if (data == NULL)
		return (NULL);
	data->cmd = line;
	data->index = 0;
	data->here_doc = 0;
	data->c = data->cmd[data->index];
	return (data);
}

/*lexer_advance ==> get forward in characters of the line*/
void	lexer_advance(t_lexer *data)
{
	if (data->c != '\0' && data->index < ft_strlen(data->cmd))
	{
		data->index += 1;
		data->c = data->cmd[data->index];
	}
	return ;
}

/*lexer_advance_withe_token  ==> go to the next character and don't lose the old
 * one */
t_token	*lexer_advance_withe_token(t_lexer *data, t_token *token)
{
	lexer_advance(data);
	return (token);
}

/*lexer_skip_withe_spaces ==> ignore the withe spaces*/
void	lexer_skip_withe_spaces(t_lexer *data)
{
	while (data->c == ' ' || data->c == '\t' || data->c == '\r')
		lexer_advance(data);
	return ;
}

/*convert the char to string by adding null character */
char	*lexer_get_char_as_string(t_lexer *data)
{
	char	*new;

	new = ft_calloc(2, sizeof(char));
	new[0] = data->c;
	new[1] = '\0';
	return (new);
}
