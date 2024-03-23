/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:54:19 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/06 18:08:02 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*return the a pointer to the last node */
t_data	*last_in_linked_list(t_data *data)
{
	while (data->next)
		data = data->next;
	return (data);
}

/*revers the linked list */
void	revers_linked_list(t_data **data)
{
	t_data	*prev;
	t_data	*cur;
	t_data	*tmp;

	cur = (*data);
	prev = NULL;
	if (*data == NULL || (*data)->next == NULL)
		return ;
	while (cur)
	{
		tmp = cur->next;
		cur->next = prev;
		prev = cur;
		cur = tmp;
	}
	free(cur);
	(*data) = prev;
}

/* free the linked list after a error happend */
void	ft_clear(t_data **data)
{
	t_data	*curr;
	t_data	*node;

	if (*data == NULL || data == NULL)
		return ;
	node = (*data);
	while (node)
	{
		curr = node->next;
		free (node->cmd);
		free(node);
		node = curr;
	}
	*data = NULL;
}

/*print data ==> print the data of linked list */
void	print_data(t_data *data)
{
	t_data	*new;

	new = data;
	while (new)
	{
		printf("-> [%s] [%d]\n", new->cmd, new->token_type);
		new = new->next;
	}
	return ;
}

/*linked len ==> calc the len of lined list return the len*/
int	linked_len(t_data *data)
{
	int	c;

	c = 0;
	while (data)
	{
		c++;
		data = data->next;
	}
	return (c);
}
