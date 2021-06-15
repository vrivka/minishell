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
# include <readline/readline.h>
# include <signal.h>

# define	BUFFER_SIZE 4096

# define	EXEC_F_NAME "msh"//debagging binary should be "msh"!
# define	HIST_F_NAME ".history"

# define	NOFLG 0b0000
# define	SQFLG 0b0001
# define	WQFLG 0b0010
# define	BSFLG 0b0100
# define	UBSFL 0b1000//flag to '\' unset

# define	ERROR_MEM		"minishell: Could not allocate memory"
# define	ERR_OPCRHISF	"minishell: Could not open/create history file"
# define	ERR_READHISF	"minishell: Could not read history file"
# define	ERR_TERMNAME	"minishell: Could not get term type from envs"
# define	ERR_TERMATTR	"minishell: Could not get term parameters"
# define	ERR_TERMCAP		"minishell: Could not look up termcap entry"
# define	ERR_SETTERM		"minishell: Could not set term parameters"
# define	ERR_READKEY		"minishell: Could not read from STDIN"
# define	ERR_SYNTAX		"minishell: Syntax error near %s"

typedef struct	s_pipe
{	
	char		*bin_path;
	char		**args;
	char		**rd;
	int			l_fd;
	int			r_fd;
}				t_pipe;

typedef struct	s_pars
{
	char	*s;
	char	*args;
	char	*rds;
	int		i;
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

	char		**semi;
	int			semi_count;
	char		flags;

	////
	char		*check_spargs;//sp flag (space is argument(1) or not(0))
	char		*check_sprds;//sp flag
	////

	int			ret;//saved return code after execve and buidins for $?. 0 by default

	int			pid;
	t_pipe		*pipe;
	int			pipe_count;

	int l_fd;
	int r_fd;
	int			**pipe_fd;
	char		*pwd;
}				t_msh;

t_msh			g_msh;

void			term_setup(void);
int				ft_putchar(int c);

void			init_msh(char **av, char **envp);
int				main_loop(void);
void			key_loop(void);

void			set_term(void);
void			unset_term(void);

////history
void			get_history(char **av);
char			*get_hist_path(char **av);
char			*read_hist2str(int fd);
char			**get_hist_array(char *str);
int				get_arr_size(char *str);
void			fill_array(char **arr, char *str);
int				get_str_len(char *str, int n);
void			put_hist2file(void);
int				count_arr_lines(char **array);
void			insert_nline2hist(void);
////

////semicolon split
void			semicolon_splitter(void);
void			init_semicolon_array(void);
int				get_semi_num(char *s);
void			set_flags(int c);
int				check_flags(void);
int				get_semiline_len(char *s);
void			fill_semicolon_array(void);
////

////parser
void			launch(void);
int				parser(char *s);
int				get_pipe_num(char *s);
void			fill_pars(t_pars *pars);
char			*del_start_sp(char *s);
char			*del_end_sp(char *s);
void			lexer(t_pars *pars);

char			*get_pipe_str(char **s);
int				get_pipestr_len(char *s);

void			redir_pars(t_pars *pars);
void			space_pars_rd(t_pars *pars);
void			dollar_pars_rd(t_pars *pars);
void			strongquotes_pars_rd(t_pars *pars);
char			*get_sq_str(t_pars *pars);
int				get_sqstr_len(char *s);
void			weakquotes_pars_rd(t_pars *pars);
void			backslash_pars_rd(t_pars *pars);
void			enlarge_rds(t_pars *pars);

void			weakquotes_pars(t_pars *pars);
void			wq_dollar_val(t_pars *pars);
void			wq_dollar_ret(t_pars *pars);

void			strongquotes_pars(t_pars *pars);
void			backslash_pars(t_pars *pars);
void			space_pars(t_pars *pars);
void			enlarge_args(t_pars *pars);

////dollar pars
void			dollar_pars(t_pars *pars);
char			*get_env_name(t_pars *pars);
void			add_sq_str(t_pars *pars, char **str);
void			add_wq_str(t_pars *pars, char **str);
char			*get_dstr(t_pars *pars);

///sp flag
void			change_sp2us(char **s);
char			**ft_spargs_split(char const *s);
char			**ft_sprds_split(char const *s);

void			args2lower(void);
////

////strings_ops - operations with string
char			*ft_strnew(size_t n);
char			*ft_strjoin_fr(char *s1, char *s2);
char			*ft_strdellstch_fr(char *s1);
char			*ft_strrewrite(char *s1, char *s2);
char			*ft_cutstr_begin(char *s, int i);//cut beginning of line by index
char			*ft_cutstr_end(char *s, int i);//cut ending of line by index
char			*ft_add_char2str(char *s, int c);//add symbol at the end of the string
char			*ft_ins_ch2str(char *s, int c, int pos);//insert char into string by index
char			**ft_devide_str(char *s, int pos);//split string to strings in a certain place
char			*ft_del_chinstr(char *s, int pos);//delete symbol before cursor (backspace)
////

////d_array_ops - operations with double array
char			**add_str2darr(char **array);

////

////env_ops - operations with environment variables array
void			copy_envs(char **envp);
char			*env_value(char **env, char *name);//vlad
char			*env_val_cut(const char *env);//vlad
int				env_finder(char **env, char *name);//vlad
int				envncmp(const char *env, const char *find);//vlad
////

////check_syntax
int				check_semi(void);
int				check_pipe(char *s);
int				check_mid_pipe(char *tmp);
int				check_sq(char *s);
int				check_wq(char *s);
////

////sig_handler
void			sig_handler(int signum);
////

////free_ops - free memory routine
void			free_d_arr(char **array);
void			free_pipe(void);
////

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
char **envcpy(char **env);
int envlen(char **env);
int check_args(char *arg);

char **free_envc(char **tmp, int i);

char **env_add(char **env, char *av, int l);
char **env_del(char **env, char *name, int l);
char *path_finder(char *env_path, char *av_null);
char *ft_strcjoin(char *s1, int c, char *s2);
int shlvl(void);
int it_builtin(int i);

int export_func(char **av);
void export_arg(char *arg);
void change_env(const char *env, int n);
void exp_env_add(char *env);
int	check_args(char *arg);
int env_func(void);
int pwd_func(void);
int cd_func(char **av);
int echo_func(char **av);
int unset_func(char **av);
int exit_func(char **av);
int exec_func(char **av);
void open_dup_pipes(int i);
void redirs(void);
void open_redirs(char **rd, int n);
int text_document(char *delim);
char *parse_redir(char *line, char **env);
char *check_dol(char *line, char *ptr_dol, int *i, char **env);
char *check_bs(char *line, const char *ptr_bs, int *i);
char *augment_char(char *line, char c);
int check_line(const char *line);
void open_left_redir(char *path, int n);
void open_double_left_redir(char *path, int n);
void open_right_redir(char *path, int n);
void open_double_right_redir(char *path, int n);
int exec_builtin(int i, int n);
int exec_without_pipes(void);
int exec_pipes(void);
void close_if(int fd1, int fd2);
void pipe_init(void);
void exec_pipe_func(char **av, int i);
int error_func(char *error_str, int exit_code, int ex_ret, char *arg);

#endif