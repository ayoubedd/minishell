NAME = minishell
FLGAG = -Wall -Wextra -Werror
INC = -Iincludes/ -I/goinfre/aeddaoud/.brew/opt/readline/include 
INC2 = -Ilibft/
CC=cc
SRC_DIR= src/parser/
OBJ_DIR= obj/

SRC_NAME = minishell.c lexer.c lexer2.c lexer3_func_token.c linked_list.c linked_list2.c \
					 parser_utils.c parser2_helper.c parser3_helper.c utils2.c token.c lexer_collect_id.c \
					 utils.c parser2.c expend_variable1_parser.c lexer_collect_special.c lexer3.c error.c\
					 utils3.c clear.c return_char.c lexer_collect_string.c error2.c \
					 file_name_input_output.c expend_varibale.c expend_variable2_parser.c parser1_helper.c
OBJ_NAME = $(SRC_NAME:%.c=%.o)
OBJECT= $(addprefix $(OBJ_DIR), $(OBJ_NAME))

EXEC_NAME = executor.c  init_cmds.c init_envs.c get_cmd_path.c envs_to_array.c handle_heredocs.c exec_cmds.c handle_stdin.c handle_stdout.c checker.c sync_stuff.c cleanup.c helpers.c pipes_helpers.c heredoc_helpers.c checker_helpers.c
EXEC_OBJ = $(EXEC_NAME:%.c=%.o)
EXEC_READY = $(addprefix $(OBJ_DIR), $(EXEC_OBJ))


BLT_NAME = exec_blt.c cd.c echo.c env.c exit.c export.c pwd.c unset.c blt_helpers.c
BLT_OBJ = $(BLT_NAME:%.c=%.o)
BLT_READY = $(addprefix $(OBJ_DIR), $(BLT_OBJ))

SIG_NAME = signal_handling.c
SIG_OBJ = $(SIG_NAME:%.c=%.o)
SIG_READY = $(addprefix $(OBJ_DIR), $(SIG_OBJ))

all : create_dir $(NAME)

create_dir:
	@mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJECT) $(EXEC_READY) $(BLT_READY) $(SIG_READY)
	@make -C libft/
	@make bonus -C libft/
	@$(CC) $(FLGAG) -o $(NAME) $(OBJECT) $(EXEC_READY) $(BLT_READY) $(SIG_READY) libft/libft.a -L/goinfre/aeddaoud/.brew/opt/readline/lib -I/goinfre/aeddaoud/.brew/opt/readline/include -lreadline

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(FLGAG) -o $@ -c $< $(INC) $(INC2)  -g

$(OBJ_DIR)%.o : src/execution/%.c
	@$(CC) $(FLGAG) -o $@ -c $< $(INC) $(INC2) -g

$(OBJ_DIR)%.o : src/builtins/%.c
	@$(CC) $(FLGAG) -o $@ -c $< $(INC) $(INC2) -g

$(OBJ_DIR)%.o : src/signals/%.c
	@$(CC) $(FLGAG) -o $@ -c $< $(INC) $(INC2) -g

clean :
	@make fclean -C libft
	@rm -rf $(OBJECT) $(EXEC_READY) $(BLT_READY) $(SIG_READY) $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)
re : fclean all
