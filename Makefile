NAME =	minishell

SRCS =	srcs/main.c\
		srcs/parser.c\
		srcs/pipe.c\
		srcs/command.c\
		srcs/args.c\
		srcs/bin.c\
		srcs/builtins.c\
		srcs/cd.c\
		srcs/export.c\
		srcs/unset.c\
		srcs/utils.c\
		srcs/len.c\
		srcs/remove.c\
		srcs/excutable.c\
		srcs/gnl.c\
		srcs/get_token.c \
		srcs/get_token_utils.c \
		srcs/error_message.c \
		srcs/word_expansion.c \
		srcs/signal_handler.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -Wunused-function
#CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

LIBFT = libft.a
LIBFTDIR = libft/
LIBFTLINK = -L $(LIBFTDIR) -lft

RL_DIR = ~/.brew/opt/readline/lib
INC_DIR = ~/.brew/opt/readline/include

all:		$(NAME)

$(NAME):	complib $(OBJS)
ifdef LINUX
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFTLINK) -lreadline
else
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFTLINK) -L $(RL_DIR) -lreadline
endif

complib:
	$(MAKE) -C libft all bonus

%.o:		%.c
ifdef LINUX
	$(CC) $(CFLAGS) -c -o $@ $^
else
	$(CC) $(CFLAGS) -c -o $@ -I $(INC_DIR) $^
endif

clean:
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
