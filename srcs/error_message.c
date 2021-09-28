#include "minishell.h"

void	errmsg_syntax(char *token)
{
	if (ft_strcmp(token, "") == 0)
		token = "newline";
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}
