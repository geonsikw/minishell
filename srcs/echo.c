/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:15:14 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/02 23:15:16 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_check(t_data *p, int i)
{
	char	*d;

	d = p->av[1 + i] + 2;
	if (!ft_memcmp(p->av[1 + i], "-n", 2))
	{
		while (*d == 'n')
		{
			d++;
			if (!*d)
				return (1);
		}
	}
	return (0);
}

void	echo_command(t_data *p, int fd)
{
	int	i;

	p->ret = 0;
	i = 0;
	while (p->ac > 1 && (n_check(p, i) || !ft_memcmp(p->av[1 + i], "-n", 3)))
	{
		i++;
		if (!p->av[1 + i])
			break ;
	}
	while (++i < p->ac)
	{
		ft_putstr_fd(p->av[i], fd);
		if (i < p->ac - 1 && ft_strlen(p->av[i + 1]))
			write(fd, " ", 1);
	}
	if (!(p->ac > 1 && (!ft_memcmp(p->av[1], "-n", 3) || n_check(p, 0))))
		write(fd, "\n", 1);
}
