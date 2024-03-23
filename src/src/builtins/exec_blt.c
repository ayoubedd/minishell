/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:10:50 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/08 16:58:00 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/builtins.h"

void	exec_blt(t_exec *exec, t_cmd *cmd, t_parser *raw, t_exmode mode)
{
	t_builtin	blt;

	blt = which_builtin(raw);
	if (blt == CD)
		cd_blt(exec, cmd);
	if (blt == ECHO)
		echo_blt(cmd);
	if (blt == ENV)
		env_blt(exec);
	if (blt == EXIT)
		exit_blt(cmd);
	if (blt == EXPORT)
		export_blt(exec, cmd);
	if (blt == PWD)
		pwd_blt(exec);
	if (blt == UNSET)
		unset_blt(exec, cmd);
	if (mode == EMBEDDED)
		exit(g_exit_code);
}
