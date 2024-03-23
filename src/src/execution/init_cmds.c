/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:15:24 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/08 14:19:05 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include "../../includes/builtins.h"

static void	add_back(t_cmd **head, t_cmd *node)
{
	t_cmd	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

static size_t	args_count(t_opt *ops)
{
	size_t	i;

	i = 0;
	while (ops)
	{
		i++;
		ops = ops->next;
	}
	return (i);
}

static char	**extract_args(t_parser *raw)
{
	t_opt	*ops;
	size_t	i;
	char	**args;

	i = 1;
	ops = raw->cmd_option;
	if (!raw->cmd)
		return (NULL);
	args = malloc((args_count(ops) + 2) * sizeof(char *));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(raw->cmd);
	while (ops)
	{
		args[i] = ft_strdup(ops->opt);
		ops = ops->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

static void	cmd_init(t_exec *exec, t_cmd *cmd, t_parser *raw)
{
	cmd->pid = -1;
	cmd->stdin = -1;
	cmd->stdout = -1;
	cmd->next = NULL;
	cmd->skip = FALSE;
	cmd->read_pipe = -1;
	cmd->doc_write_fd = -1;
	cmd->env = exec->env_arr;
	cmd->args = extract_args(raw);
	cmd->builtin = which_builtin(raw);
	cmd->path = get_cmd_path(exec->env, raw->cmd);
}

t_cmd	*init_cmds(t_exec *exec)
{
	t_cmd		*head;
	t_cmd		*cmd;
	t_parser	*raw;

	head = NULL;
	raw = exec->raw;
	while (raw)
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			return (NULL);
		cmd_init(exec, cmd, raw);
		add_back(&head, cmd);
		raw = raw->next;
	}
	return (head);
}
