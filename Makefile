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
		tools/ft_lstadd_back.c \
		src/parse.c\
		src/words.c\
		src/pipe.c\
		src/outfile_append.c \
		src/infile_herdoc.c \
		src/copy_env.c 

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