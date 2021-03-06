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
# include <dirent.h>

# define	BUFFER_SIZE 64

# define	EXEC_F_NAME "minishell"
# define	HIST_F_NAME ".history"

# define	NOFLG 0b00000000
# define	SQFLG 0b00000001
# define	WQFLG 0b00000010
# define	BSFLG 0b00000100
# define	UBSFL 0b00001000

# define	ERROR_MEM		"minishell: Could not allocate memory"
# define	ERR_OPCRHISF	"minishell: Could not open/create history file"
# define	ERR_READHISF	"minishell: Could not read history file"
# define	ERR_TERMNAME	"minishell: Could not get term type from envs"
# define	ERR_TERMATTR	"minishell: Could not get term parameters"
# define	ERR_TERMCAP		"minishell: Could not look up termcap entry"
# define	ERR_SETTERM		"minishell: Could not set term parameters"
# define	ERR_READKEY		"minishell: Could not read from STDIN"
# define	ERR_SYNTAX		"minishell: Syntax error near %s"

typedef struct s_pipe
{	
	char	*bin_path;
	char	**args;
	char	**rd;
	int		l_fd;
	int		r_fd;
}	t_pipe;

typedef struct s_pars
{
	char	*s;
	char	*args;
	char	*rds;
	int		i;
}	t_pars;

typedef struct s_msh
{
	char			*term_name;
	struct termios	*term;
	char			*hist_path;
	char			**history;
	int				h_size;
	int				h_index;
	int				pos;
	char			**envp;
	char			*line;
	char			**semi;
	int				semi_count;
	char			flags;
	char			*check_spargs;
	char			*check_sprds;
	int				ret;
	int				pid;
	t_pipe			*pipe;
	int				pipe_count;
	int				rdfl;
	int				**pipe_fd;
	char			*pwd;
}	t_msh;

t_msh	g_msh;

void	term_setup(void);
int		ft_putchar(int c);
void	init_msh(char **av, char **envp);
void	main_loop(void);
void	reinit_history(void);
void	clean_line(void);
void	key_loop(void);
void	wait4signals(void);
void	welcome_promt(void);
int		key_decisions(char *buf, int c, int len);
void	key_up_func(void);
void	key_down_func(void);
void	key_left_func(void);
void	key_right_func(void);
void	key_bs_func(void);
void	key_ctrld_func(void);
void	key_print_func(char *buf, int c, int len);
int		key_enter_func(void);
void	set_term(void);
void	unset_term(void);
void	get_history(char **av);
char	*get_hist_path(char **av);
char	*read_hist2str(int fd);
char	**get_hist_array(char *str);
int		get_arr_size(char *str);
void	fill_array(char **arr, char *str);
int		get_str_len(char *str, int n);
void	put_hist2file(void);
int		count_arr_lines(char **array);
void	insert_nline2hist(void);
void	semicolon_splitter(void);
void	init_semicolon_array(void);
int		get_semi_num(char *s);
void	set_flags(int c);
int		check_flags(void);
int		get_semiline_len(char *s);
void	fill_semicolon_array(void);
void	launch(void);
void	parser(char *s);
void	pars_init(t_pars *pars);
int		get_pipe_num(char *s);
void	repair(int i);
void	repair_empty_rd(int i);
void	repair_empty_args(int i);
void	fill_pars(t_pars *pars);
char	*del_start_sp(char *s);
char	*del_end_sp(char *s);
void	lexer(t_pars *pars);
void	free_tmp_vars(t_pars *pars);
char	*get_pipe_str(char **s);
int		get_pipestr_len(char *s);
void	redir_pars(t_pars *pars);
void	space_pars_rd(t_pars *pars);
void	dollar_pars_rd(t_pars *pars);
void	strongquotes_pars_rd(t_pars *pars);
char	*get_sq_str(t_pars *pars);
int		get_sqstr_len(char *s);
void	weakquotes_pars_rd(t_pars *pars);
void	wq_bsbs_pars_rd(t_pars *pars);
void	wq_bswq_pars_rd(t_pars *pars);
void	wq_bsdol_pars_rd(t_pars *pars);
void	backslash_pars_rd(t_pars *pars);
void	enlarge_rds(t_pars *pars);
void	place_space(t_pars *pars);
void	place_rd_symbols(t_pars *pars);
void	weakquotes_pars(t_pars *pars);
void	wq_bsbs_pars(t_pars *pars);
void	wq_bswq_pars(t_pars *pars);
void	wq_bsdol_pars(t_pars *pars);
void	wq_dolbs_pars(t_pars *pars);
void	wq_doldig_pars(t_pars *pars);
void	wq_enlarge_args(t_pars *pars);
void	wq_dollar_val(t_pars *pars);
void	wq_dollar_ret(t_pars *pars);
void	strongquotes_pars(t_pars *pars);
void	backslash_pars(t_pars *pars);
void	space_pars(t_pars *pars);
void	enlarge_args(t_pars *pars);
void	dollar_pars(t_pars *pars);
char	*get_env_name(t_pars *pars);
void	add_sq_str(t_pars *pars, char **str);
void	add_wq_str(t_pars *pars, char **str);
char	*get_dstr(t_pars *pars);
void	change_sp2us(char **s);
char	**ft_spargs_split(char const *s);
char	**ft_sprds_split(char const *s);
void	args2lower(void);
char	*ft_strnew(size_t n);
char	*ft_strjoin_fr(char *s1, char *s2);
char	*ft_strdellstch_fr(char *s1);
char	*ft_strrewrite(char *s1, char *s2);
char	*ft_cutstr_begin(char *s, int i);
char	*ft_cutstr_end(char *s, int i);
char	*ft_add_char2str(char *s, int c);
char	*ft_ins_ch2str(char *s, int c, int pos);
char	*ft_del_chinstr(char *s, int pos);
char	**add_str2darr(char **array);
char	**ins_str2arr(char **arr, int n);
char	**ft_devide_str(char *s, int pos);
void	copy_envs(char **envp);
char	*env_value(char **env, char *name);
char	*env_val_cut(const char *env);
int		env_finder(char **env, char *name);
int		envncmp(const char *env, const char *find);
int		check_syntax(char *s);
int		check_semi(void);
int		check_pipe(char *s);
int		check_mid_pipe(char *tmp);
int		check_sq(char *s);
int		check_wq(char *s);
int		check_empty(char *s);
int		check_rd(char *s);
int		check_drd(char *s);
int		check_alone_rd(int i, int n);
void	sig_handler_promt(int signum);
void	sig_handler_exec(int signum);
void	free_d_arr(char **array);
void	free_pipe(void);

/* Vrivka's functions */

void	executor(void);
char	**envcpy(char **env);
int		envlen(char **env);
int		check_args(char *arg);
char	**free_envc(char **tmp, int i);
char	**env_add(char **env, char *av, int l);
char	**env_del(char **env, char *name, int l);
char	*path_finder(char *env_path, char *av_null);
char	*ft_strcjoin(char *s1, int c, char *s2);
int		shlvl(void);
int		it_builtin(int i);
int		export_func(char **av);
void	export_arg(char *arg);
void	change_env(const char *env, int n);
void	exp_env_add(char *env);
int		check_args(char *arg);
int		env_func(void);
int		pwd_func(void);
int		cd_func(char **av);
int		echo_func(char **av);
int		unset_func(char **av);
int		exit_func(char **av);
int		exec_func(char **av);
void	signals_check(char **av);
void	open_dup_pipes(int i);
void	redirs(void);
void	open_redirs(char **rd, int n);
int		text_document(char *delim);
char	*parse_redir(char *line, char **env);
char	*check_dol(char *line, char *ptr_dol, int *i, char **env);
char	*check_bs(char *line, const char *ptr_bs, int *i);
char	*augment_char(char *line, char c);
int		check_line(const char *line);
void	open_left_redir(char *path, int n);
void	open_double_left_redir(char *path, int n);
void	open_right_redir(char *path, int n);
void	open_double_right_redir(char *path, int n);
int		exec_builtin(int i, int n);
int		exec_without_pipes(void);
int		exec_pipes(void);
void	check_dir(char *arg, int st);
void	close_if(int fd1, int fd2);
void	pipe_init(void);
void	exec_pipe_func(char **av, int i);
int		error_func(char *error_str, int exit_code, int ex_ret, char *arg);

//
int		check_exec_name(char *bin, char *name);
//

//
int		main_loop_rd(int fd, char *delim);
int		key_loop_rd(void);
int		key_decisions_rd(char *buf, int c, int len);
void	key_bs_func_rd(void);
void	key_left_func_rd(void);
void	key_right_func_rd(void);
void	key_print_func_rd(char *buf, int c, int len);
void	key_ctrlc_func_rd(void);
void	wait4signal_rd(void);
void	sig_handler_promt_rd(int signum);
void	unset_term_rd(void);
void	set_term_rd(void);
//
#endif