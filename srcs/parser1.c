/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 20:02:38 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/03 13:00:02 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(t_list **token_list, char *line)
{
	char	*token;
	int		type;
	int		err;

	if (get_token(&token, &type, &line) < 0)
		err = -ETOKEN;
	else
		err = parse_line(token_list, &token, &type, &line);
	if (!err && type != EOL)
		err = -ESYNTAX;
	if (err == -ESYNTAX)
	{
		ft_lstclear(token_list, free);
		errmsg_syntax(token);
		free(token);
	}
	else if (err == -ETOKEN)
	{
		ft_lstclear(token_list, free);
		ft_putendl_fd("minishell: quote not closed", 2);
	}
	else
		free(token);
	return (err);
}

static char	**get_array_from_list(t_list **token_list, int size)
{
	char	**arr;
	t_list	*tmp;

	arr = malloc(sizeof(char *) * ((size_t)size + 1));
	arr[size] = 0;
	while (--size >= 0)
	{
		arr[size] = (char *)(*token_list)->content;
		tmp = *token_list;
		*token_list = (*token_list)->next;
		free(tmp);
	}
	return (arr);
}

void	parser(t_data *p)
{
	t_list	*token_list;

	if (!p->str)
		p->cmds = NULL;
	else
		p->cmds = ft_strldup(p->str, ft_strlen(p->str));
	token_list = 0;
	if (parse(&token_list, p->cmds) == 0)
	{
		p->ac = ft_lstsize(token_list);
		p->av = get_array_from_list(&token_list, p->ac);
		command_or_pipe(p);
		free_matrix(p->av);
	}
	else
		p->ret = 2;
	free(p->str);
	p->str = 0;
	free(p->cmds);
}
