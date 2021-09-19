/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:42:24 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/19 13:12:01 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_p(t_data *p)
{
	free(p->str);
	free_matrix(p->envp);
	free_matrix(p->export);
	free_matrix(p->av);
	free(p->cmds);
	free(p);
}

void	exit_command(t_data *p)
{
	int	i;

	if (p->ac > 2)
	{
		ft_putstrs_fd("exit\n", "bash: exit: too many arguments\n", 0, 2);
		p->ret = 1;
	}
	else
	{
		i = 0;
		while (p->ac > 1 && ft_isdigit(p->av[1][i]))
		{
			i++;
		}
		if (p->ac > 1 && p->av[1][i])
		{
			ft_putstrs_fd("exit\nbash: exit: ",
				p->av[1], ": numeric argument required\n", 2);
			p->ret = 255;
		}
		if (p->ac > 1 && p->ret != 255)
			i = ft_atoi(p->av[1]);
		else
			i = p->ret;
		free_p(p);
		exit(i);
	}
}
