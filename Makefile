NAME = msh

LIBFT_PATH = libft/

LIBFT = $(LIBFT_PATH)libft.a

PARS = pars.a

SRCS = main.c \
		key_loop.c \
		string_ops.c \
		d_array_ops.c \
		history.c \
		free_ops.c \
		semi_split.c \
		parser.c \
		redir_pars.c \
		dollar_pars.c \
		weakquotes_pars.c \
		env_ops.c \
		ft_spargs_split.c \
		ft_sprds_split.c \
		check_syntax.c \
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
        vrivka/open_redirs_utils.c \
        vrivka/path_finder.c \
        vrivka/pwd_func.c \
        vrivka/unset_func.c

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
		-I./includes -ltermcap -lreadline -o msh

.PHONY: all clean fclean re