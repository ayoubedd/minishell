/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:45:07 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/08 17:41:46 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/builtins.h"

static void	go_to_dir(t_exec *exec, char *path)
{
	char	*cwd;

	if (chdir(path))
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(path);
		g_exit_code = 1;
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("minishell: getcwd ", STDERR_FILENO);
		perror(NULL);
		return ;
	}
	exenv_insert_var(&exec->env, "PWD", cwd);
	exenv_insert_var(&exec->env, "OLDPWD", exec->cwd);
	free(exec->cwd);
	free(cwd);
	exec->cwd = getcwd(NULL, 0);
	g_exit_code = 0;
}

static void	go_to_var(t_exec *exec, char *var)
{
	t_exenv	*tmp;

	tmp = find_item(exec->env, var);
	if (!tmp)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(var, STDERR_FILENO);
		ft_putstr_fd(" is not set.\n", STDERR_FILENO);
		g_exit_code = 1;
		return ;
	}
	go_to_dir(exec, tmp->value);
}

void	cd_blt(t_exec *exec, t_cmd *cmd)
{
	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "~"))
		return (go_to_var(exec, "HOME"));
	if (!ft_strcmp(cmd->args[1], "-"))
		return (go_to_var(exec, "OLDPWD"));
	go_to_dir(exec, cmd->args[1]);
}
