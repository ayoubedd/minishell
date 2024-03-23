/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:10:33 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/07 18:51:20 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include "../../includes/signals.h"

static void	heredoc(int fd, t_env **env, t_file *doc)
{
	char	*expanded;
	char	*line;

	while (TRUE)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(doc->file_name, line))
		{
			free(line);
			break ;
		}
		if (doc->token_type == 5)
			expanded = expand_input(env, line);
		else
			expanded = line;
		ft_putstr_fd(expanded, fd);
		ft_putstr_fd("\n", fd);
		free(expanded);
	}
}

static void	handle_cmd_heredocs(t_cmd *cmd, t_parser *raw, t_env **env)
{
	t_list	*list;
	t_file	*file;
	int		fd[2];

	list = raw->file_input;
	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		exit(EXIT_FAILURE);
	}
	while (list)
	{
		file = list->content;
		if (file->type == HEREDOC)
		{
			if (is_last_heredoc(list->next) && cmd->doc_write_fd != -1)
				heredoc(cmd->doc_write_fd, env, file);
			else
				heredoc(fd[1], env, file);
		}
		list = list->next;
	}
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		perror("minishell: close");
}

t_bool	handle_cmds_heredocs(t_cmd *cmd, t_parser *raw, t_env **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (TRUE);
	}
	if (pid == 0)
	{
		signal(SIGINT, &doc_sig_handler);
		while (cmd && raw)
		{
			handle_cmd_heredocs(cmd, raw, env);
			cmd = cmd->next;
			raw = raw->next;
		}
		exit(EXIT_SUCCESS);
	}
	wait_heredoc_process();
	if (g_exit_code == 0)
		return (FALSE);
	else
		return (TRUE);
}

static void	check_max_heredocs(t_parser *raw)
{
	if (heredocs_count(raw->file_input) > 16)
	{
		ft_putstr_fd("minishell: maximum here-document \
		count exceeded\n", STDERR_FILENO);
		exit(2);
	}
}

t_bool	handle_heredocs(t_cmd *cmd, t_env **env, t_parser *raw)
{
	t_cmd		*t_cmd;
	t_parser	*t_raw;
	int			fd[2];

	t_cmd = cmd;
	t_raw = raw;
	while (t_raw && t_cmd)
	{
		check_max_heredocs(t_raw);
		if (input_type(t_raw) == INPUT_HEREDOC)
		{
			if (pipe(fd) == -1)
			{
				perror("minishell: pipe");
				return (TRUE);
			}
			t_cmd->doc_write_fd = fd[1];
			t_cmd->stdin = fd[0];
		}
		t_cmd = t_cmd->next;
		t_raw = t_raw->next;
	}
	return (handle_cmds_heredocs(cmd, raw, env));
}
