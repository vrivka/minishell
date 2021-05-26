NAME = a.out

LIBFT_PATH = libft/

LIBFT = $(LIBFT_PATH)libft.a

HEADER = test.h

SRCS =	main.c \
        envcpy.c \
        env_finder.c \
        env_func.c \
        pwd_func.c \
        echo_func.c \
        export_func.c \
        frees_inits.c \
        cd_func.c \
        path_finder.c \
        error_func.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

SANFLAGS = -g3 -fsanitize=address

RM = rm -f

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
		@gcc $(CFLAGS) -o $(NAME) $(LIBFT) $^

$(LIBFT):
		@make -C libft

%.o:	%.c
		@gcc $(CFLAGS) -c $< -o $@ -I.

clean:
		@make clean -C libft
		@$(RM) $(OBJS)

fclean:	clean
		@make fclean -C libft
		@$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re