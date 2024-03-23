/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:17:52 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/13 00:07:52 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sig_int_handler(int sig)
{
	(void)sig;
	if (errno == EINTR)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 1;
		return ;
	}
	if (g_exit_code == 0)
		g_exit_code = 130;
}

void	doc_sig_handler(int sig)
{
	(void)sig;
	printf("\n");
	exit(EXIT_FAILURE);
}

void	signal_handling(void)
{
	signal(SIGINT, &sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
}
