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
		gcc -g $(CFLAGS) $(SRCS) $(LIBFT) $(EXEC) \
		-I./includes -ltermcap

.PHONY: all clean fclean re