NAME = msh

LIBFT_PATH = libft/

LIBFT = $(LIBFT_PATH)libft.a

EXEC_PATH = vrivka/

EXEC = $(EXEC_PATH)executor.a

PARS = pars.a

SRCS = main.c \
		string_ops.c \
		d_array_ops.c \
		history.c \
		free_ops.c \
		parser.c \
		env_ops.c

# for debug
VSRCS = vrivka/cd_func.c \
		vrivka/echo_func.c \
		vrivka/env_finder.c \
		vrivka/env_func.c \
		vrivka/envcpy.c \
		vrivka/error_func.c \
		vrivka/exec_func.c \
		vrivka/executor.c \
		vrivka/exit_func.c \
		vrivka/export_func.c \
		vrivka/frees_inits.c \
		vrivka/path_finder.c \
		vrivka/pwd_func.c \
		vrivka/unset_func.c
# 

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

all:	$(NAME)

$(NAME):	$(PARS) $(LIBFT) $(EXEC)
		@gcc $(CFLAGS) -o $(NAME) $^ -ltermcap

$(PARS):	$(OBJS)
		@ar rcs $(PARS) $?

%.o:	%.c
		@gcc $(CFLAGS) -o $@ -c $< -I./includes

$(LIBFT):
		@make -C $(LIBFT_PATH)

$(EXEC):
		@make -C $(EXEC_PATH)

clean:
		@make clean -C $(LIBFT_PATH)
		@make clean -C $(EXEC_PATH)
		@$(RM) $(OBJS)

fclean:	clean
		@make fclean -C $(LIBFT_PATH)
		@make fclean -C $(EXEC_PATH)
		@$(RM) $(PARS)
		@$(RM) $(NAME)

re:		fclean all

dbg:
		gcc -g $(CFLAGS) $(SRCS) $(LIBFT) $(VSRCS) \
		-I./includes -ltermcap

.PHONY: all clean fclean re