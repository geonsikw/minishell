#include "minishell.h"

int	isopchar(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	isquotechar(char c)
{
	return (c == '"' || c == '\'');
}

int	iswordchar(char c)
{
	return (c && !ft_isblank(c) && !isopchar(c));
}
