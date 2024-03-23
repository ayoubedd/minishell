/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 12:37:11 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/12 21:52:32 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_lst(t_list **lst)
{
	t_list	*node;
	t_list	*cur;

	node = *lst;
	if (*lst == NULL || lst == NULL)
		return ;
	while (node)
	{
		cur = node->next;
		free (node->content);
		free (node);
		node = cur;
	}
	*lst = NULL;
}

void	clear_opt(t_opt **node)
{
	t_opt	*cur;
	t_opt	*opt;

	opt = *node;
	if (*node == NULL || node == NULL)
		return ;
	while (opt)
	{
		cur = opt->next;
		free (opt);
		opt = cur;
	}
	*node = NULL;
}

void	ft_clear_all(t_parser **parser)
{
	t_parser	*node;
	t_parser	*cur3;

	if (*parser == NULL || parser == NULL)
		return ;
	node = *parser;
	while (node)
	{
		cur3 = node->next;
		clear_opt(&node->cmd_option);
		clear_lst (&node->file_input);
		clear_lst (&node->file_output);
		free (node);
		node = cur3;
	}
	*parser = NULL;
}

void	giga_clear(t_parser **parse, t_data **data)
{
	ft_clear_all (parse);
	ft_clear(data);
}
