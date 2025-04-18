/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:32 by ychedmi           #+#    #+#             */
/*   Updated: 2025/04/18 11:25:48 by ychedmi          ###   ########.fr       */
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
    REDIRECT_IN,    
    REDIRECT_OUT,  
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
    char	**append;
	struct s_env *next;
}	t_parce;

// --------------------------- DISPLAY ----------------------- //
void	display_env(t_env *list);
void	disp_ar(char **str);
// --------------------------- TOOLS ----------------------- //
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_isspace(int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_token *ft_lstlast(t_token *lst);
void    ft_lstadd_back(t_token **lst, t_token *new);
t_token *ft_lstnew(void *content);

// ------------------------ TOKENIZATION ----------------------- //
void	main_parse(char *s);
int		red_infile(t_token **token);
int		red_outfile(t_token **token);
int		here_doc(t_token **token);
int		infile_heredoc(char *s, t_token **head);
int		words(char *s, t_token **head);
int		is_spcharc(char c);
int		skip_space(char *s);
int		outfile_append(char *s, t_token **head);
int		append(t_token **token);
int		handle_pipe(char *s, t_token **head);
int		ft_lenspace(char *s);
int		check_words(char *s, t_token **head);
int		doub_qt(char *s);


// ------------------------ COPY_ENV ----------------------- //
t_env   *lstnew_env(void *name, void *value);
void    env_add_back(t_env **lst, t_env *new);
void	ft_lstdelone(t_env *lst);
void	copy_env(t_env **head);
int     len_equal(char *s);

int		valid_word(char *s);

// ------------------------ parse_data ----------------------- //
void	infile_data(t_token **head, t_parce *newnode);
void	outfile_data(t_token **head, t_parce *newnode);
void	append_data(t_token **head, t_parce *newnode);
void	heredoc_data(t_token **head, t_parce *newnode);
void	word_data(t_token **head, t_parce *newnode);
// ------------------------ free_data ----------------------- //
void	ft_lstclear(t_token **lst);
void	doubfree(char **s)
# endif