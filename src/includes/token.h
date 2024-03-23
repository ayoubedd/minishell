/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:09:43 by hlahrach          #+#    #+#             */
/*   Updated: 2022/07/23 22:20:32 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/*define token heder witch contain the token that we are gonna deling with */
typedef enum s_token
{
	TOKEN_PIPE,
	TOKEN_INPUT,
	TOKEN_OUTPUT,
	TOKEN_HERDOC,
	TOKEN_APPEND,
	TOKEN_ID,
	TOKEN_SPACES,
	TOKEN_D_QOTES,
	TOKEN_S_QOTES,
	TOKEN_PARENTS,
	TOKEN_SIMI,
	TOKEN_FLAGE,
	TOKEN_AND_OP,
	TOKEN_OR_OP,
	TOKEN_OTHER,
}	t_token_type;

typedef struct s_toke
{
	t_token_type	token_type;
	char			*value;
}	t_token;

t_token	*init_token(int type, char *val);

#endif
