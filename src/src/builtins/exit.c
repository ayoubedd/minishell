/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:31:39 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/11 15:44:46 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"

static t_bool	check_overflow(char *nums)
{
	int		tmp;
	size_t	i;

	i = 0;
	if (!nums)
		return (FALSE);
	tmp = ft_atoi(nums);
	if (tmp > 0 && nums[0] == '-')
		return (TRUE);
	else if ((tmp < 0 && nums[0] == '+')
		|| (tmp < 0 && (nums[0] >= '0' && nums[0] <= '9')))
		return (TRUE);
	i++;
	return (FALSE);
}

static t_bool	check_syntax(char *nums)
{
	int	j;

	if (nums[0] == '-' || nums[0] == '+')
		j = 1;
	else
		j = 0;
	while (nums[j])
	{
		if (!(nums[j] >= '0' && nums[j] <= '9'))
			return (TRUE);
		j++;
	}
	return (FALSE);
}

static t_bool	check_exit_arg(char *arg)
{
	if (check_syntax(arg) || check_overflow(arg))
		return (FALSE);
	return (TRUE);
}

static size_t	args_count(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	return (i - 1);
}

void	exit_blt(t_cmd *cmd)
{
	size_t	count;

	count = args_count(cmd->args);
	if (count == 0)
		exit(EXIT_SUCCESS);
	if (!check_exit_arg(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(255);
	}
	if (count > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_exit_code = 1;
		return ;
	}
	exit(ft_atoi(cmd->args[1]));
}
