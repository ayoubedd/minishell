/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:19:55 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/06 17:53:10 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_input(t_env **env, char *input)
{
	char	*tmp;

	tmp = parser_expend_variable(input, env);
	free(input);
	return (tmp);
}

void	wait_heredoc_process(void)
{
	int	res;

	while (wait(&res) != -1)
		;
	g_exit_code = WEXITSTATUS(res);
}

size_t	heredocs_count(t_list *list)
{
	t_file	*input;
	size_t	count;

	count = 0;
	while (list)
	{
		input = list->content;
		if (input->type == HEREDOC)
			count++;
		list = list->next;
	}
	return (count);
}
