#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <term.h>
# include <termios.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>

# define	BUFFER_SIZE 4096
# define	EXEC_F_NAME "a.out"//change to "msh" before final compilation
# define	HIST_F_NAME "history"//change to ".history" before final compilation

typedef struct	s_pars
{
	char		**args;
	int			n;//index in line
	int			j;//index of args
}				t_pars;

typedef struct	s_msh
{
	char		*term_name;
	struct		termios	*term;
	char		*hist_path;
	char		**history;
	int			h_size;//number of history lines
	int			h_index;//current position in history array
	int			pos;//current position in read line in terminal
	int			status;//main_loop return status after command execution
	char		**envp;
	char		*line;//read line
	int			ret;//saved return code after execve and buidins for $?. 0 by default

	int			pid;
	t_pars		pars;
}				t_msh;

t_msh			g_msh;

void			term_setup(t_msh *msh);
int				ft_putchar(int c);

void			init_msh(t_msh *msh, char **av, char **envp);
void			main_loop(t_msh *msh);
void			key_loop(t_msh *msh);

//history
void			get_history(t_msh *msh, char **av);
char			*get_hist_path(char **av);
char			*read_hist2str(int fd);
char			**get_hist_array(char *str);
int				get_arr_size(char *str);
void			fill_array(char **arr, char *str);
int				get_str_len(char *str, int n);
void			put_hist2file(t_msh *msh);
int				count_arr_lines(char **array);
void			insert_nline2hist(t_msh *msh);
//

//parser
void			parser(t_msh *msh);
char			*del_start_sp(char *s);
char			*get_env_name(t_msh *msh);
int				get_envname_len(char *s);
char			*get_sq_str(t_msh *msh);
int				get_sqstr_len(char *s);
void			args2lower(t_pars *pars);
void			dollar_pars(t_msh *msh, t_pars *pars);
void			strongquotes_pars(t_msh *msh, t_pars *pars);
void			weakquotes_pars(t_msh *msh, t_pars *pars);
void			backslash_pars(t_msh *msh, t_pars *pars);
void			space_pars(t_msh *msh, t_pars *pars);
void			enlarge_arg(t_msh *msh, t_pars *pars);
//

//strings_ops - operations with string
char			*ft_strnew(size_t n);
char			*ft_strjoin_fr(char *s1, char *s2);
char			*ft_strdellstch_fr(char *s1);
char			*ft_strrewrite(char *s1, char *s2);
char			*ft_cutline(char *s1, int i);//cut line by index from beginning
char			*ft_add_char2str(char *s, int c);//add symbol at the end of the string
//

//d_array_ops - operations with double array
char			**add_str2darr(char **array);

//

//env_ops - operations with environment variables array
void			copy_envs(t_msh *msh, char **envp);
char			*env_value(char **env, char *name);//vlad
char			*env_val_cut(const char *env);//vlad
int				env_finder(char **env, char *name);//vlad
int				envncmp(const char *env, const char *find);//vlad
//

//free_ops - free memory routine
void			free_d_arr(char **array);
//

// typedef struct s_exec
// {
//    char *bin_path;
//    char **args;
//    int flag;
//    int redir;
//    struct s_exec *next;
// } t_exec;




/* Vrivka's functions */

void executor(void);
void all_init(char **env);
char **envcpy(char **env);
int envlen(char **env);

void all_free(void);
char **free_envc(char **tmp, int i);

char **env_add(char *av);
char **env_del(char *name);

int export_func(char **av);
int env_func(void);
int pwd_func(void);
int cd_func(char **av);
int echo_func(char **av);
int exec_func(char **av);
int error_func(char *error_str, int exit_code, int ex_ret, char *arg);

#endif