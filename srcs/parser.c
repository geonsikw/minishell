/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 20:02:38 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/17 19:57:17 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_data *p)
{
	p->cmds = ft_strdup(p->str);
	p->ac = count_args(p->cmds);
	p->av = ft_calloc(sizeof(char *), p->ac + 1);
	set_args(p->av, p->cmds, p->ac);
	command_or_pipe(p);
	free_matrix(p->av);
	free(p->cmds);
}
