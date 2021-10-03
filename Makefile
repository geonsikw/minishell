# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/02 23:26:31 by jihkwon           #+#    #+#              #
#    Updated: 2021/10/03 12:24:07 by gwoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRCS =	srcs/bin.c \
		srcs/cd.c \
		srcs/command.c \
		srcs/echo.c \
		srcs/env.c \
		srcs/environment.c \
		srcs/error_message.c \
		srcs/exit.c \
		srcs/export1.c \
		srcs/export2.c \
		srcs/field.c \
		srcs/get_token.c \
		srcs/here_document.c \
		srcs/len.c \
		srcs/main.c \
		srcs/parser1.c \
		srcs/parser2.c \
		srcs/pipe.c \
		srcs/redirection.c \
		srcs/remove.c \
		srcs/signal_handler.c \
		srcs/unset.c \
		srcs/utils1.c \
		srcs/utils2.c \
		srcs/word_expansion1.c \
		srcs/word_expansion2.c \
		srcs/word_expansion3.c \

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address
#CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

LIBFT = libft/libft.a
LIBFTDIR = libft/
LIBFTLINK = -L $(LIBFTDIR) -lft

RL_DIR = ~/.brew/opt/readline/lib
INC_DIR = ~/.brew/opt/readline/include

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
ifdef LINUX
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFTLINK) -lreadline
else
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFTLINK) -L $(RL_DIR) -lreadline
endif

$(LIBFT) :
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
