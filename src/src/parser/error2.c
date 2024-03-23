/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 19:06:58 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/06 17:52:39 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_error2(t_minshell **minishell,
		t_data **data, t_parser **parse)
{
	ft_error ("syntax error: unexpected end of file \n", 4);
	giga_clear (parse, data);
	g_exit_code = 258;
	(*minishell)->exit_error = 258;
}

void	syntax_error3(t_minshell **minishell,
		t_data **data, t_parser **parse)
{
	ft_error ("syntax error near unexpected token `newline' \n", 1);
	giga_clear (parse, data);
	g_exit_code = 285;
	(*minishell)->exit_error = 258;
}
