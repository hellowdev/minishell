CC = cc

READLINE = $(shell brew --prefix readline)
CFLAGS = -Wall -Wextra -Werror -I$(READLINE)/include
MINIFLAGS =  -lreadline -lncurses -L$(READLINE)/lib -g -Wl,-no_pie

NAME = minishell

SRC = 	minishell.c \
		tools/ft_doubjoin.c\
		tools/ft_split.c \
		tools/ft_calloc.c \
		tools/ft_memcpy.c \
		tools/ft_isdigit.c \
		tools/ft_isalpha.c \
		tools/ft_strdup.c \
		tools/ft_strjoin.c \
		tools/ft_strlen.c \
		tools/ft_isspace.c \
		tools/ft_lstnew.c \
		tools/ft_substr.c \
		tools/ft_strcmp.c \
		tools/ft_itoa.c \
		tools/ft_atoi.c \
		tools/ft_slash_join.c\
		tools/ft_lstadd_back.c \
		tools/ft_putstr_fd.c\
		tools/ft_lstsize.c\
		tools/ft_isslash.c\
		tools/get_next_line.c\
		tools/get_next_line_utils.c\
		parse/parsing.c\
		token/main_token.c\
		token/token_words.c\
		token/outfile_append.c \
		token/infile_herdoc.c \
		parse/copy_env.c\
		parse/valid_word.c\
		parse/get_data.c\
		parse/forfree.c\
		parse/count_data.c\
		parse/deljoin.c\
		expand_status/expand.c\
		expand_status/qoute_expand.c\
		expand_status/expand_tools.c\
		expand_status/syntax_error.c\
		expand_status/expand_cmd.c\
		execution/main_execute.c\
		execution/children.c\
		execution/dup_in.c\
		execution/dup_out.c\
		execution/exec_cmd.c\
		execution/heredoc_tools.c\
		execution/here_doc.c\
		execution/creat_tmp.c\
		execution/dup_heredoc.c\
		execution/path_checker.c\
		built_in/built_env.c\
		built_in/built_cd.c\
		built_in/built_pwd.c\
		built_in/built_echo.c\
		built_in/built_unset.c\
		built_in/built_export.c\
		built_in/built_exit.c\
		signals.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)  $(MINIFLAGS) -lreadline -lncurses

%.o : %.c minishell.h
	@$(CC) $(CFLAGS)  -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

ac: all clean