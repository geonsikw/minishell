/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 20:02:38 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/16 04:29:04 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_str(char *s)
{
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)ft_calloc(sizeof(char), 2);
	str = ft_strldup(s, ft_strlen(s));
	return (str);
}

void	parser(t_data *p)
{
	int	i;

	i = 0;
	p->cmds = copy_str(p->str);
	p->ac = count_args(p->cmds);
	p->av = (char **)ft_calloc(sizeof(char *), (p->ac + 1));
	set_args(p->av, p->cmds, p->ac);
	while (p->av[i])
		i++;
	command_or_pipe(p);
	free_matrix(p->av);
	free(p->str);
	p->str = 0;
	free(p->cmds);
}
