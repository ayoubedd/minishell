/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:58:43 by hlahrach          #+#    #+#             */
/*   Updated: 2022/07/24 12:59:07 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*nesert lexer*/
void	insert_lexer(t_data **data, t_token *token)
{
	ft_insert(data, token);
	return ;
}

void	base_line_case(char *line)
{
	if (ft_strlen(line) != 0)
		add_history(line);
	return ;
}

/* insert the enverment varibla */
void	insert_env(t_env **env, char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		insert_linked_end_env(env, ft_strdup(data[i]));
		i++;
	}
}

void	parser_clear(t_parser **parser)
{
	t_parser	*tmp;
	t_parser	*cur;

	tmp = (*parser);
	if (parser == NULL || *parser == NULL)
		return ;
	while (tmp)
	{
		cur = tmp->next;
		free (tmp);
		tmp = cur;
	}
	free (cur);
	*parser = NULL;
}
