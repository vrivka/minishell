#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include "libft.h"
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_pars
{
	char *bin_path;
	char **args;
	int flag;
	int redir;
	struct s_exec *next;
} t_pars;

typedef struct s_all
{
	t_pars *pars;
	char *pwd;
	char **envc;
	int ret;
} t_all;

t_all g_msh;

void all_init(char **env);
char **envcpy(char **env);
int envlen(char **env);


void all_free(void);
char **free_envc(char **tmp, int i);


int env_finder(char **env, char *name);
char *env_value(char **env, char *name);
char **env_add(char *av);
char **env_del(char *name);
int exec_func(char **av);
int error_func(char *error_str, int exit_code, int ex_ret, char *arg);

int export_func(char **av);
int env_func(void);
int pwd_func(void);
int cd_func(char **av);
int echo_func(char **av);

#endif
