/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:15:34 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/03 12:55:17 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_command(t_data *p, int fd)
{
	int	i;

	p->ret = 0;
	if (p->ac != 1)
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		p->ret = 1;
		return ;
	}
	i = 0;
	while (p->envp[i])
		ft_putstrs_fd(p->envp[i++], "\n", 0, fd);
}
