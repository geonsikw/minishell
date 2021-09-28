#include "minishell.h"

int	get_quote_len(char *str)
{
	char	*p;

	p = ft_strchr(str + 1, *str);
	if (!p)
		return (-1);
	return ((int)(p - str) + 1);
}

int	get_token_len(char *line)
{
	int	i;
	int	qlen;

	if (ft_strncmp(line, "<<", 2) == 0 || ft_strncmp(line, ">>", 2) == 0)
		return (2);
	if (isopchar(*line))
		return (1);
	i = 0;
	while (iswordchar(line[i]))
		if (isquotechar(line[i]))
		{
			qlen = get_quote_len(line + i);
			if (qlen < 0)
				return (-1);
			i += qlen;
		}
		else
			i++;
	return (i);
}

int	get_token_type(char *token)
{
	if (ft_strcmp(token, "") == 0)
		return (EOL);
	if (ft_strcmp(token, "<<") == 0)
		return (DLESS);
	if (ft_strcmp(token, ">>") == 0)
		return (DGREAT);
	if (isopchar(token[0]))
		return (token[0]);
	return (WORD);
}

int	get_token(char **token, int *type, char **line)
{
	int	len;

	while (ft_isblank(**line))
		++*line;
	len = get_token_len(*line);
	if (len < 0)
		return (-1);
	*token = ft_strldup(*line, len);
	*line += len;
	*type = get_token_type(*token);
	return (0);
}
