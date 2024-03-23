/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:59:59 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/11 19:43:10 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef enum e_bool {
	FALSE,
	TRUE
}	t_bool;

typedef enum e_output_type {
	OUTPUT_STDOUT,
	OUTPUT_FILE,
	OUTPUT_FILE_APPEND,
	OUTPUT_PIPE
}	t_output_type;

typedef struct s_cmd {
	char			*path;
	char			**args;
	char			**env;
	int				stdin;
	int				stdout;
	int				read_pipe;
	int				builtin;
	int				doc_write_fd;
	pid_t			pid;
	t_bool			skip;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec_env {
	char				*key;
	char				*value;
	struct s_exec_env	*next;
}	t_exenv;

typedef struct e_exec
{
	t_parser	*raw;
	t_cmd		*cmd;
	t_exenv		*env;
	char		*cwd;
	char		**env_arr;
}	t_exec;

typedef enum e_input_type {
	INPUT_FILE,
	INPUT_HEREDOC,
	INPUT_PIPE,
	INPUT_STD
}	t_input_type;

void			executor(t_minshell *mini);
t_exenv			*init_envs(t_env *env);
t_cmd			*init_cmds(t_exec *execution);
char			*get_cmd_path(t_exenv *env, char *cmd);
char			**envs_to_array(t_exenv *env);
t_bool			handle_heredocs(t_cmd *cmd, t_env **env, t_parser *raw);
t_bool			exec_cmds(t_exec *exec);
int				handle_stdin(t_cmd *cmd, t_parser *raw);
int				handle_stdout(t_cmd *cmd, t_parser *raw);
void			checker(t_exec *exec);
void			sync_stuff(t_exec *exec, t_minshell *mini);
void			cleanup(t_exec *exec);
t_input_type	input_type(t_parser *cmd);
void			cpy_to_buffer(char *s1, char *s2, char *str);
void			cleanup_close_pipes(t_cmd *cmd);
void			kill_children(t_cmd *cmd);
t_file			*last_input(t_list *list);
t_output_type	output_type(t_parser *cmd);
t_bool			is_last_heredoc(t_list *list);
char			*expand_input(t_env **env, char *input);
void			wait_heredoc_process(void);
size_t			heredocs_count(t_list *list);
t_bool			check_file_exist(t_file *file);

#endif