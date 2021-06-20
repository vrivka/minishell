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
		vrivka/cd_func.c \
        vrivka/echo_func.c \
        vrivka/env_func.c \
        vrivka/env_handler.c \
        vrivka/envcpy.c \
        vrivka/error_func.c \
        vrivka/exec_func.c \
        vrivka/exec_pipe_func.c \
        vrivka/exec_utils.c \
        vrivka/executor.c \
        vrivka/exit_func.c \
        vrivka/export_func.c \
        vrivka/export_func_utils.c \
        vrivka/free_shlvl.c \
        vrivka/open_redirs.c \
		vrivka/key_loop_rd.c \
		vrivka/key_func_rd.c \
		vrivka/term_setup_rd.c \
		vrivka/open_redirs_signals.c \
        vrivka/open_redirs_utils.c \
        vrivka/path_finder.c \
        vrivka/pwd_func.c \
        vrivka/unset_func.c \
        vrivka/text_handler.c

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

dbg:
		gcc -g $(CFLAGS) $(SRCS) $(LIBFT) \
		-I./includes -ltermcap -lreadline -o minishell

.PHONY: all clean fclean re