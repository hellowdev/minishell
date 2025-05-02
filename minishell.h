/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:32 by ychedmi           #+#    #+#             */
/*   Updated: 2025/05/02 12:43:57 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <term.h>           // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h>  // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>   // add_history, rl_clear_history
# include <stdbool.h>

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
    char    *value;
    t_type  type;
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
	struct s_parce *next;
}	t_parce;

typedef struct s_word
{
    char    *strdb;
    char    *strsg;
    char    *str;
    int     i;
}   t_word;
// --------------------------- DISPLAY ----------------------- //
void	display_env(t_env *list);
void	disp_ar(char **str);

// --------------------------- TOOLS ----------------------- //

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_isspace(int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_token *ft_lstlast(t_token *lst);
void    ft_lstadd_back(t_token **lst, t_token *new);
t_token *ft_lstnew(void *content, t_type type);
int     ft_strcmp(char *s1, char *s2);

// ------------------------ TOKENIZATION ----------------------- //

void	main_parse(t_env *env, char *s);
int		red_infile(t_token **token);
int		red_outfile(t_token **token);
int		here_doc(t_token **token);
int		infile_heredoc(char *s, t_token **head);
int		skip_space(char *s);
int		outfile_append(char *s, t_token **head);
int		append(t_token **token);
int		handle_pipe(char *s, t_token **head);
int     join_word(char *s, t_token **head);
int		check_words(char *s, t_token **head);
int		doub_qt(char *s, t_word *data);
int     sing_qt(char *s, t_word *data);
int     spec_char(char c);
void	tokenization(char *s, t_token **head);
int     check_chac(char *s, t_word *data);

// ------------------------ COPY_ENV ----------------------- //

t_env   *lstnew_env(void *name, void *value);
void    env_add_back(t_env **lst, t_env *new);
void	copy_env(t_env **head);
int     len_equal(char *s);

// ------------------------ ALLOCATE_DATA ----------------------- //

int     count_cmd(t_token *head, t_parce *newnode, t_env *env);
int     count_infiles(t_token *head, t_parce *newnode, t_env *env);
int		count_outfiles(t_token *head, t_parce *newnode, t_env *env);
int		count_heredoc(t_token *head, t_parce *newnode, t_env *env);
t_parce	*data_alloc(t_token *head, t_env *env);

// ------------------------ PARCE_DATA ----------------------- //

void    update_status(t_env *env);
int     get_infile(t_token *head, int i, t_parce *newnode, t_env *env);
int     get_cmd(t_token *head, int i, t_parce *newnode, t_env *env);
int     get_outfile(t_token *head, int i, t_parce *newnode, t_env *env);
int     get_herdoc(t_token *head, int i, t_parce *newnode, t_env *env);
void    pars_ing(t_parce **lst, t_env *env, t_token *head);
int		valid_word(t_token *head);
int		is_spcharc(char c);
void	parse_add_back(t_parce **lst, t_parce *new);

// ------------------------ free_data ----------------------- //

void	ft_lstclear(t_token *lst);
void	doubfree(char **s);
void	free_doublst(t_parce *head);
void	free_env(t_env *head);
# endif
