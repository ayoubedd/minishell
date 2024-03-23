/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:45:51 by hlahrach          #+#    #+#             */
/*   Updated: 2022/07/24 11:47:26 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
the implemenntation the linked list
*/

/*ft_creat ==> creat and return new node */
t_data	*ft_creat(t_token *token)
{
	t_data	*data;

	if (token == NULL)
		perror("NULL node");
	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		perror("error malloc ");
	data->cmd = token->value;
	data->token_type = token->token_type;
	data->next = NULL;
	free(token);
	return (data);
}

/*ft_insert ==> insert a node at front of linked list */
void	ft_insert(t_data **data, t_token *token)
{
	t_data	*new;
	t_data	*node;

	node = *data;
	new = ft_creat(token);
	if (new == NULL)
		return ;
	if ((*data) == NULL || data == NULL)
	{
		(*data) = new;
		return ;
	}
	else
		while (node && node->next)
			node = node->next;
	node->next = new;
	return ;
}

// linked list nev ==============================
t_env	*ft_creat_env(char *s)
{
	t_env	*data;

	if (s == NULL)
		perror("NULL node");
	data = (t_env *)malloc(sizeof(t_env));
	if (data == NULL)
		perror("error malloc ");
	data->env = s;
	data->next = NULL;
	return (data);
}

/*ft_insert ==> insert a node at front of linked list */
void	ft_insert_env(t_env **data, char *s)
{
	t_env	*new;

	new = ft_creat_env(s);
	if (new == NULL)
		return ;
	if ((*data) == NULL)
		(*data) = new;
	else
	{
		new->next = *data;
		*data = new;
	}
	return ;
}

// =============== end =========================
void	insert_linked_end_env(t_env **data, char *s)
{
	t_env	*tmp;
	t_env	*new;

	new = ft_creat_env(s);
	if (new == NULL)
		perror("memory allocation faild ");
	if (data == NULL || *data == NULL)
	{
		*data = new;
	}
	else
	{
		tmp = (*data);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return ;
}
