/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:16:32 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/03 18:01:36 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_command(t_data *p)
{
	long long	exitcode;

	ft_putendl_fd("exit", 2);
	if (p->ac == 1)
		exitcode = p->ret;
	else if (!ft_atoll(&exitcode, p->av[1]))
	{
		ft_putstrs_fd(
			"minishell: exit: ", p->av[1], ": numeric argument required\n", 2);
		exitcode = 255;
	}
	else if (p->ac != 2)
	{
		p->ret = 1;
		return (ft_putendl_fd("minishell: exit: too many arguments", 2));
	}
	free_p(p);
	exit((int)exitcode);
}
