all:
	gcc -g -Wall -Wextra -Werror \
	minishell.c \
	string_ops.c \
	d_array_ops.c \
	history.c \
	free_ops.c \
	parser.c \
	env_ops.c \
	./libft/libft.a -ltermcap