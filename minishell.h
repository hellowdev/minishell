/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:32 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/03 13:48:49 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>          // printf
# include <stdlib.h>         // malloc, free, exit, getenv
# include <string.h>         // strerror
# include <unistd.h>         // write, read, access, close, fork, execve, getcwd, chdir, dup, dup2, isatty, ttyname, ttyslot
# include <fcntl.h>          // open
# include <errno.h>          // perror, strerror
# include <sys/wait.h>       // wait, waitpid, wait3, wait4
# include <signal.h>         // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>       // stat, lstat, fstat
# include <dirent.h>         // opendir, readdir, closedir
# include <termios.h>        // tcsetattr, tcgetattr
# include <sys/ioctl.h>      // ioctl
# include <term.h>     	     // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h>  // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <ncurses.h>  // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>   // add_history, rl_clear_history
# include <stdbool.h>
#include <limits.h>

extern int		status;
extern char **environ;

typedef enum s_type
{
	WORD,
	PIPE,
	RED_IN,
	RED_OUT,
	APPEND,
	HEREDOC
}   t_type;

typedef struct s_token
{
	char	*value;
	t_type	type;
	struct s_token *next;
}   t_token;

 
typedef struct s_env
{
	char	*name_env;
	char	*value_env;
	struct s_env *next;
}	t_env;


typedef struct s_parce
{
	char	**cmd;
	char	**infiles;
	char	**outfiles;
	char	**heredoc;
	bool	*append;
	bool	input;
	bool	check_qt;
	struct s_parce *next;
}	t_parce;

typedef struct s_word
{
	char    *p;
	int     i;
}   t_word;

typedef struct s_expand
{
	t_env	*env;
}   t_expand;

typedef struct s_child
{
	t_env	**env;
	int		*status;
	int		check;
	int		pipefd[2];
	int		newpipe[2];
	int		*ids;
	int		i;
}   t_child;

// --------------------------- DISPLAY ----------------------- //
void	display_env(t_env *list);
void	disp_ar(char **str);
// --------------------------getnxtline------------------------//
char	*get_next_line(int fd);
char	*join(char *str1, char *str2);
char	*takeme(char *holder);
int		new_line(char *buff);
char	*afternwl(char *str);
// --------------------------- TOOLS ----------------------- //
int		ft_isdigit(int c);
char	**ft_doubjoin(char **tab1, char **tab2);
int		ft_isalpha(int c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_isspace(int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void    ft_lstadd_back(t_token **lst, t_token *new);
t_token *ft_lstnew(void *content, t_type type);
int     ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
char	*ft_slash_join(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
int		ft_lstsize(t_parce *lst);
int		ft_atoi(const char *str, int *e);
int		ft_sizeenv(t_env *lst);
char	*skip_sp(char *s);

// ------------------------ TOKENIZATION ----------------------- //

t_parce	*main_parse(char *s, t_env *env);
int		red_infile(t_token **token);
int		red_outfile(t_token **token);
int		here_doc(t_token **token);
int		infile_heredoc(char *s, t_token **head);
int		outfile_append(char *s, t_token **head);
int		append(t_token **token);
int		handle_pipe(char *s, t_token **head);
int		check_words(char *s, t_token **head);
int		doub_qt(char *s, char **str, bool *checker);
int		doub_quote(char *s);
int		sing_quote(char *s);
int     sing_qt(char *s, char **str);
void	tokenization(char *s, t_token **head);

// ------------------------ COPY_ENV ----------------------- //

t_env   *lstnew_env(void *name, void *value);
void    env_add_back(t_env **lst, t_env *new);
void	copy_env(t_env **head);
int     len_equal(char *s);

// ------------------------ ALLOCATE_DATA ----------------------- //

int     count_cmd(t_token *head, t_parce *newnode, t_env *env);
int     count_infiles(t_token *head, t_parce *newnode, t_env *env);
int		count_outfiles(t_token *head, t_parce *newnode, t_env *env);
int		count_heredoc(t_token *head, t_parce *newnode);
t_parce	*data_alloc(t_token *head, t_env *env);

// ------------------------ PARCE_DATA ----------------------- //

int     get_infile(t_token *head, t_parce *newnode, t_env *env);
int     get_cmd(t_token *head, t_parce *newnode, t_env *env);
int     get_outfile(t_token *head, t_parce *newnode, t_env *env);
int     get_herdoc(t_token *head, t_parce *newnode);
void    pars_ing(t_parce **lst, t_token *head, t_env *env);
int     valid_word(char *s);
int		is_spcharc(char c);
void	parse_add_back(t_parce **lst, t_parce *new);
int     double_qt(char *s);
int     single_qt(char *s);
char	*deljoin(char *s, bool *check_quote);
char	**word_to_cmd(char *str, t_env *env, bool inside_dq);

// ------------------------ expansion ----------------------- //
int		calc_qout(char *s);
int		strlen_dol(char *s);
void    update_status(char *s);
char	*expand_status(char *head, t_env *env, bool checker);
int		not_exp(char *s, char **value);
int		expand(char *s, char **value, t_env *env);
int		simple_word(char *s, char **value);
int		check_dol_sp(char *s);
int		special_char(char c);
char	*env_searsh(t_env *env, char *name);
// ------------------------ free_data ----------------------- //
void	free_null(char **s);
void	ft_lstclear(t_token *lst);
void	doubfree(char **s);
void	free_doublst(t_parce **head);
void	free_env(t_env *head);
// ------------------------ PATH_CMD ----------------------- //
char	**wich_path(t_env *env);
char	*valid_path(t_env *env, char *cmd);
// ------------------------ EXECUTION_FUNCTIONS ----------------------- //
void	execute(t_parce *data, t_env **env);
void	one_child(t_parce **data, t_child *pack);
void	first_child(t_parce **data, t_child *pack);
int		listofchild(t_parce **data, t_child *pack);
void	last_child(t_parce **data, int oldtmp, t_child *pack);
int		i_child(t_parce *data, int oldpipe, int *pipefd, t_child *pack);
int		check_infile(char **infile);
int		dup_infile(char **infile, bool check);
int		check_outfile(char **outfile, bool *append);
int		dup_outfile(char **outfile, bool *append);
int		count_fd(char **fds);
int		execute_cmd(t_parce *data, t_env *testenv);
int		redire_err(char *file, char *err);
void	fd_closer(int fd, int *pipefd);
void	wait_proc(t_child *pack);
// ------------------------ HEREDOC_FUNC ----------------------- //
int		dup_heredoc(char **heredoc, bool input, int index);
int		ft_strcm_doc(char *s1, char *s2);
void	creat_file(char **heredoc, bool quoted, int index, t_expand *stock);
char	*file_name(int index);
void	creat_file(char **heredoc, bool quoted, int index, t_expand *stock);
int		heredoc(t_parce **data, t_env *env);
int		strlen_herdoc(char *s);
void	del_file(t_parce *nodes);
int		double_len(char **cmd);
// ------------------------ BUILTIN_CMD ----------------------- //
int		built_in(t_parce *data, t_env **env);
void	env_cmd(t_env *env);
int		match_cmd(char *user_cmd, char *matcha);
void	cd_cmd(char **cmd, t_env **env);
void	pwd_cmd(char **cmd);
void	echo_cmd(char **cmd);
void	unset_cmd(char **cmd, t_env **env);
void	export_cmd(char **cmd, t_env **env);
int		valid_idf(char *s);
void	exit_cmd(t_parce *data, char **cmd, t_env *env);
// ------------------------ SIGNALS ----------------------- //
void	disable_ctrl_echo();
void	handle_signals(int sig);
void	signalss();
# endif
