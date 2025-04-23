CC = cc

CFLAGS = -Wall -Wextra -Werror 

NAME = minishell

SRC = 	minishell.c \
		display.c \
		tools/ft_split.c \
		tools/ft_bzero.c \
		tools/ft_calloc.c \
		tools/ft_memcpy.c \
		tools/ft_strdup.c \
		tools/ft_strjoin.c \
		tools/ft_strlen.c \
		tools/ft_isspace.c \
		tools/ft_lstnew.c \
		tools/ft_substr.c \
		tools/ft_lstlast.c \
		tools/ft_strcmp.c \
		tools/ft_lstadd_back.c \
		parse/parse.c\
		token/words.c\
		token/tokenz.c\
		token/pipe.c\
		token/outfile_append.c \
		token/infile_herdoc.c \
		parse/copy_env.c\
		parse/valid_word.c\
		parse/get_data.c\
		parse/forfree.c\
		parse/count_data.c\
		parse/update_status.c\


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lreadline -lncurses $(OBJ) -o $(NAME)

%.o : %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

ac: all clean