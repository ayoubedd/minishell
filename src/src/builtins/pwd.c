/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:39:23 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/08 17:42:48 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"

void	pwd_blt(t_exec *exec)
{
	if (!exec->cwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n", STDERR_FILENO);
		g_exit_code = 1;
		return ;
	}
	printf("%s\n", exec->cwd);
	g_exit_code = 0;
}
