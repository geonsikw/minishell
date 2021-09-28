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
		srcs/get_token.c \
		srcs/get_token_utils.c \
		srcs/error_message.c \
		srcs/word_expansion.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

LIBFT = libft.a
LIBFTDIR = libft/
LIBFTLINK = -L $(LIBFTDIR) -lft


all:		$(NAME)

$(NAME):	complib $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFTLINK)

complib:
	$(MAKE) -C libft all bonus

%.o:		%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(OBJS)
	$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
