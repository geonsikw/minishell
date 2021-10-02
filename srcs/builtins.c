/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:32:40 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/02 21:24:32 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	**multiple_env(t_data *p, int fd)
{
	int	i;

	p->ret = 0;
	if (!ft_memcmp(p->av[0], "export", 7) && p->ac == 1
		&& !ft_strlen(p->av[1]))
	{
		sort_envp(p->envp, fd, '=');
		sort_envp(p->export, fd, 0);
	}
	i = 1;
	reset(p);
	while (p->av[i])
	{
		if (!ft_memcmp(p->av[0], "export", 7))
		{
			if (check_export_error(p->av, &i))
				p->ret = 1;
			else
				export_value(p, &i);
		}
		else if (!ft_memcmp(p->av[0], "unset", 6))
			p->envp = unset_command(p, i++);
	}
	return (p->envp);
}
*/

/*
void	exit_command(t_data *p)
{
	int	i;
	int ret;

	i = 0;
	if (p->ac > 2)
	{
		while (p->ac > 1 && ft_isdigit(p->av[1][i]))
			i++;
		if (p->ac > 1 && p->av[1][i])
		{
			ft_putstrs_fd("exit\nbash: exit: ",
				p->av[1], ": numeric argument required\n", 2);
			p->ret = 255;
			ret = p->ret;
			free_p(p);
			exit(ret);
		}
		else
			ft_putstrs_fd("exit\n", "bash: exit: too many arguments\n", 0, 2);
		p->ret = 1;
	}
	else
	{
		while (p->ac > 1 && ft_isdigit(p->av[1][i]))
			i++;
		if (p->ac > 1 && p->av[1][i])
		{
			ft_putstrs_fd("exit\nbash: exit: ",
				p->av[1], ": numeric argument required\n", 2);
			p->ret = 255;
			ret = p->ret;
			free_p(p);
			exit(ret);
		}
		else
			ft_putstr_fd("exit\n", 2);
		if (p->ac > 1)
			i = ft_atoi(p->av[1]);
		else
			i = p->ret;
		free_p(p);
		exit(i);
	}
}
*/
