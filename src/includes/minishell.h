/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:56:09 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/12 22:28:38 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "lexer.h"
# include "token.h"
# include "parser.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>

# define KRED  "\x1B[31m"
# define KWHT  "\x1B[37m"
# define KGRN  "\x1B[32m"
# define KBLU  "\x1B[34m"

extern int	g_exit_code;

/* ========== strcut data ============ */
typedef struct s_data
{
	char			*cmd;
	int				token_type;
	struct s_data	*next;
}	t_data;

/* copy envirment varibale*/
typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}	t_env;

/* struct share between parser and executer*/
typedef struct s_minishell
{
	t_parser	*parser;
	t_env		*env;
	int			exit_error;
	char		*cwd;
}	t_minshell;

typedef enum e_type_file {
	DEFAULT,
	APPEND,
	HEREDOC,
}	t_file_type;
/* file name outupte and appende */
typedef struct s_file
{
	char		*file_name;
	t_file_type	type;
	int			last;
	int			token_type;
}	t_file;

/*=========== is here doc or file input ===================*/
typedef struct s_finput
{
	char			*file_name;
	t_file_type		type;
	int				last;
}	t_finput;

/*==============================================*/
t_parser	*init_parser(void);
void		print_data(t_data *data);
int			isempty(t_data **data);
int			linked_len(t_data *data);
t_data		*ft_creat(t_token *token_type);
void		ft_insert(t_data **data, t_token *token_type);
void		*ft_realloc(void *ptr, size_t len);
int			ft_error(char *s, int n);
void		revers_linked_list(t_data **data);
void		ft_clear(t_data **data);
/*=============== lexer ================ */
t_token		*lexer_collect_string(t_lexer *lexer,
				int token_type, char c);
void		insert_lexer(t_data **data, t_token *token);
int			lexer_get_next_token(t_lexer *data, t_data **node);
/* ======================= lexer funct ==================== */
int			lexer_base_case(t_lexer *data, t_data **node, t_token *token);
int			lexer_func_check_token(t_lexer *data, t_data **node);
int			lexer_func_check_token2(t_lexer *data, t_data **node,
				t_token *token);
t_token		*lexer_collect_special(t_lexer *lexer, int token_type);
t_token		*lexer_collect_id(t_lexer *lexer, int token_type);
t_token		*lexer_collect_string(t_lexer *lexer,
				int token_type, char c);
char		*lexer_collect_id2(t_lexer *lexer, char c);
char		*lexer_collect_id3(t_lexer *lexer, char c);
char		*lexer_collect_id4(t_lexer *lexer);
void		ft_malloc(char **tmp, char **val);
char		*lexer_collect_test(t_lexer *lexer, char c);
char		*lexer_collect2(t_lexer *lexer, char c);
char		*return_char(t_lexer *lexer);
/* ==================      parser part    ==============*/
int			convert_lexer(t_data **lexer);
char		*parser_new_string(char *s, t_env **env_data, int token_type);
void		parser_dollar_sighne(t_data **lexer, t_env **env);
void		parser_parse_lexer(t_data **lexern, t_parser **root);
int			parser_lexer_helper(t_data **tmp,
				t_parser **root, t_parser **parser);
int			parser_lexer_helper2(t_data **tmp,
				t_parser **root, t_parser **parser);
int			parser_lexer_helper5(t_data **tmp,
				t_parser **root, t_parser **parser);
int			parser_lexer_helper3(t_data **tmp,
				t_parser **root, t_parser **parser);
int			parser_lexer_helper4(t_data **tmp,
				t_parser **root, t_parser **parser);
void		insert_parser(t_parser **root, t_parser *parser);
void		insert_parser_here(t_parser **parser, char *s);
void		insert_parser_opt(t_parser **parser, char *s);
int			check_token(char *s);
void		parser_defaulth(t_parser *parser);
int			check_tokentype(int token_type);
int			return_pointer(char *s, char c, int l);
char		*expende_path2(char *s, t_env *env, int i, int *len);
char		*parser_expend_variable(char *s, t_env **env_data);
void		return_char_exp(char s, char **tmp2);
char		*convert_char_to_string(char c);
int			convert_lexer(t_data **lexer);
char		*parser_change_the_string(char *s, int token_type);
char		*parser_get_string(char *s, char c);
int			calc(char *s);
int			check_token_type(char c);
int			syntax_error(t_data **lexer);
/* env imlemenation */
void		insert_linked_end_env(t_env **data, char *s);
// ================== utils =========================
int			ft_strcmp(const char *s1, const char *s2);
int			check_case2(t_lexer *lexer);
int			check_case(t_lexer *lexer);
void		print_cmd(t_parser **parser, t_data **data);
void		insert_env(t_env **env, char **data);
void		parser_clear(t_parser **parser);
void		base_line_case(char *line);
void		ft_clear_all(t_parser **parser);
void		giga_clear(t_parser **parse, t_data **data);
void		syntax_error2(t_minshell **minishell,
				t_data **data, t_parser **parse);
void		syntax_error3(t_minshell **minishell,
				t_data **data, t_parser **parse);
void		ft_clear_env(t_env **env);
void		ft_clear_lexer(t_lexer **lexer);
t_file		*file_name(char *name, char *tmp1, t_data **tmp);
t_file		*file_name_input(char *name, char *tmp1, t_data **tmp);
void		is_singleqoutes(char c, int *n, int check);
int			parser_lexer_pipe(t_data **tmp, t_parser **root,
				t_parser **parser);
void		copy_path(char *s, t_env **env_data, char **new, int *i);
void		return_char_exp2(char s, char **tmp2, int *check);
int			check_not_empty(t_lexer **lexer);
#endif
