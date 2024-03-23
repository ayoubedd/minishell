/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:09:32 by hlahrach          #+#    #+#             */
/*   Updated: 2022/07/23 21:49:37 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"

typedef struct s_lexer
{
	char			c;
	char			*cmd;
	int				here_doc;
	unsigned int	index;
}	t_lexer;

t_lexer	*init_lexer(char *line);
void	lexer_advance(t_lexer *data);
t_token	*lexer_advance_withe_token(t_lexer *data, t_token *token);
void	lexer_skip_withe_spaces(t_lexer *data);
char	*lexer_get_char_as_string(t_lexer *data);
#endif
