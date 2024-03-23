/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:41:42 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/09 14:15:07 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*toknize the line by spliting it to each specefic part */
int	lexer_get_next_token(t_lexer *data, t_data **node)
{
	t_token	*token;
	int		n;

	token = NULL;
	while (data->c != '\0' && data->index < ft_strlen(data->cmd))
	{
		if ((data->c == ' ' || data->c == '\t'))
			lexer_skip_withe_spaces(data);
		n = lexer_base_case (data, node, token);
		if (n == 0)
			continue ;
		else if (n == 2)
			return (1);
		n = lexer_func_check_token(data, node);
		if (n != 0)
			continue ;
		n = lexer_func_check_token2 (data, node, token);
		if (n != 0 && n != 1)
			continue ;
		else if (n == 1)
			return (1);
		lexer_advance(data);
	}
	return (0);
}
