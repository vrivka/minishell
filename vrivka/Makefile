NAME = executor.a

HEADER = test.h

SRCS =	envcpy.c \
        env_finder.c \
        env_func.c \
        pwd_func.c \
        echo_func.c \
        export_func.c \
        frees_inits.c \
        cd_func.c \
        path_finder.c \
        executor.c \
        error_func.c \
        exec_func.c \
        unset_func.c \
        exit_func.c \
        exec_pipe_func.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all:	$(NAME)

$(NAME):	$(OBJS)
		@ar rcs $(NAME) $?

%.o:	%.c
		@gcc $(CFLAGS) -c $< -o $@ -I../includes

clean:
		@$(RM) $(OBJS)

fclean:	clean
		@$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re