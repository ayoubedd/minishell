/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:12:15 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/12 17:52:51 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/builtins.h"

static t_bool	is_valid_option(char *str)
{
	size_t	i;

	i = 1;
	if (!str)
		return (TRUE);
	if (str[0] != '-')
		return (TRUE);
	if (str[i] == '\0')
		return (TRUE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static size_t	skip_options(char *args[])
{
	size_t	i;

	i = 1;
	while (args[i])
	{
		if (is_valid_option(args[i]))
			return (i);
		i++;
	}
	return (i);
}

void	echo_blt(t_cmd *cmd)
{
	size_t	i;
	t_bool	ln_brk;

	ln_brk = TRUE;
	i = skip_options(cmd->args);
	if (i > 1)
		ln_brk = FALSE;
	while (cmd->args[i])
	{
		if (!cmd->args[i + 1])
			printf("%s", cmd->args[i]);
		else
			printf("%s ", cmd->args[i]);
		i++;
	}
	if (ln_brk)
		printf("\n");
	g_exit_code = 0;
}
