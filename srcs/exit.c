/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:16:32 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/02 23:17:08 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_command(t_data *p)
{
	int	exitcode;

	ft_putendl_fd("exit", 2);
	if (p->ac == 1)
		exitcode = p->ret;
	else if (!digits_only(p->av[1]))
	{
		ft_putstrs_fd(
			"minishell: exit: ", p->av[1], ": numeric argument required\n", 2);
		exitcode = 2;
	}
	else if (p->ac == 2)
		exitcode = ft_atoi(p->av[1]);
	else
	{
		p->ret = 1;
		return (ft_putendl_fd("minishell: exit: too many arguments", 2));
	}
	free_p(p);
	exit(exitcode);
}
