/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:17:40 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/05 14:37:22 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_token(int type, char *val)
{
	t_token	*data;

	if (val == NULL)
		return (NULL);
	data = ft_calloc(1, sizeof(t_token));
	data->token_type = type;
	data->value = val;
	return (data);
}
