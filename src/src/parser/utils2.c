/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:58:08 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/12 22:28:52 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*isempty ==> check if the linked list is empty or not */
int	isempty(t_data **data)
{
	if (*data == NULL)
		return (1);
	return (0);
}

void	ft_clear_env(t_env **env)
{
	t_env	*node;
	t_env	*cur;

	node = *env;
	while (node)
	{
		cur = node->next;
		free (node);
		node = cur;
	}
	*env = NULL;
}

int	check_not_empty(t_lexer **lexer)
{
	if (ft_strcmp((*lexer)->cmd, "") == 0)
	{
		free ((*lexer)->cmd);
		free (*lexer);
		return (1);
	}
	return (0);
}
