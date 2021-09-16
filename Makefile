NAME			= minishell

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
INCS			= .
RM				= rm -f
LIBC			= ar rc

SRCS_DIR		= srcs
LIBFT_DIR		= libft
LIBFT_LIB		= libft.a

SRC				= main.c \
				  parser.c \
				  pipe.c \
				  command.c \
				  args.c \
				  bin.c \
				  builtins.c \
				  cd.c \
				  utils.c \
				  utils2.c

OBJ				= $(SRC:.c=.o)

SRCS			= $(addprefix $(SRCS_DIR)/, $(SRC))
OBJS			= $(addprefix $(SRCS_DIR)/, $(OBJ))


all : $(NAME)
	$(CC) $(CFLAGS) $(NAME) srcs/main.c -o minishell

$(NAME) : $(OBJS)
	make all -C $(LIBFT_DIR)/
	cp $(LIBFT_DIR)/$(LIBFT_LIB) $@
	$(LIBC) $@ $^
	
fclean : clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

clean :
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

re : fclean all

.PHONY		: all fclean clean re
.SILENT		:
