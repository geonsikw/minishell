NAME			= minishell

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
INCS			= .
RM				= rm -f
LIBC			= ar rc

SRCS_DIR		= srcs
LIBFT_DIR		= libft
LIBFT_LIB		= libft.a

RL_DIR			= libreadline
INC_DIR			= include

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

$(NAME) : $(OBJS)
	make all -C $(LIBFT_DIR)
ifdef LINUX
	$(CC) $(CFLAGS) -o $(NAME) -I $(INC_DIR) $^ -L $(LIBFT_DIR) -lft -lreadline
else
	$(CC) $(CFLAGS) -o $(NAME) -I $(INC_DIR) $^ -L $(LIBFT_DIR) -lft -L $(RL_DIR) -lreadline
endif

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJS)
	make fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY		: all fclean clean re
