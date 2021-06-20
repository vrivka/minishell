NAME = minishell

LIBFT_PATH = libft/

LIBFT = $(LIBFT_PATH)libft.a

PARS = pars.a

SRCS = main.c \
		key_loop/key_loop.c \
		key_loop/key_funcs1.c \
		key_loop/key_funcs2.c \
		utils/env_ops.c \
		utils/string_ops1.c \
		utils/string_ops2.c \
		utils/d_array_ops.c \
		utils/free_ops.c \
		utils/utils1.c \
		utils/utils2.c \
		semicolon/semi_split.c \
		semicolon/semi_utils.c \
		parser/parser.c \
		parser/pipe_str_ops.c \
		parser/lexer.c \
		parser/redir_pars1.c \
		parser/redir_pars2.c \
		parser/dollar_pars.c \
		parser/dollar_pars_utils.c \
		parser/weakquotes_pars.c \
		parser/weakquotes_pars_utils.c \
		parser/weakquotes_pars_rd.c \
		parser/ft_spargs_split.c \
		parser/ft_sprds_split.c \
		parser/parser_utils.c \
		parser/repair.c \
		parser/delete_spaces.c \
		syntax/check_syntax1.c \
		syntax/check_syntax2.c \
		signals.c \
		history/history.c \
		history/history_utils.c \
		builtins_and_execution/cd_func.c \
        builtins_and_execution/echo_func.c \
        builtins_and_execution/env_func.c \
        builtins_and_execution/env_handler.c \
        builtins_and_execution/envcpy.c \
        builtins_and_execution/error_func.c \
        builtins_and_execution/exec_func.c \
        builtins_and_execution/exec_pipe_func.c \
        builtins_and_execution/exec_utils.c \
        builtins_and_execution/executor.c \
        builtins_and_execution/exit_func.c \
        builtins_and_execution/export_func.c \
        builtins_and_execution/export_func_utils.c \
        builtins_and_execution/free_shlvl.c \
        builtins_and_execution/open_redirs.c \
		builtins_and_execution/key_loop_rd.c \
		builtins_and_execution/key_func_rd.c \
		builtins_and_execution/term_setup_rd.c \
		builtins_and_execution/open_redirs_signals.c \
        builtins_and_execution/open_redirs_utils.c \
        builtins_and_execution/path_finder.c \
        builtins_and_execution/pwd_func.c \
        builtins_and_execution/unset_func.c \
        builtins_and_execution/text_handler.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

all:	$(NAME)

$(NAME):	$(PARS) $(LIBFT)
		@gcc $(CFLAGS) -o $(NAME) $^ -ltermcap -lreadline

$(PARS):	$(OBJS)
		@ar rcs $(PARS) $?

%.o:	%.c
		@gcc $(CFLAGS) -o $@ -c $< -I./includes

$(LIBFT):
		@make -C $(LIBFT_PATH)

clean:
		@make clean -C $(LIBFT_PATH)
		@$(RM) $(OBJS)

fclean:	clean
		@make fclean -C $(LIBFT_PATH)
		@$(RM) $(PARS)
		@$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re