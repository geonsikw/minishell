/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:32:40 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/16 04:33:04 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_command(t_data *p, int fd)
{
	int	i;

	i = 0;
	if (p->ac != 1)
	{
		ft_putstrs_fd("env: ‘", p->av[1], "’: Permission denied\n", 2);
		p->ret = 126;
		return ;
	}
	while (p->envp[i])
		ft_putstrs_fd(p->envp[i++], "\n", 0, fd);
}

void	echo_command(t_data *p, int fd)
{
	int	i;

	i = 0;
	if (p->ac > 1 && !ft_memcmp(p->av[1], "-n", 3))
		i = 1;
	while (++i < p->ac)
	{
		ft_putstr_fd(p->av[i], fd);
		if (i < p->ac - 1 && ft_strlen(p->av[i + 1]))
			write(fd, " ", 1);
	}
	if (!(p->ac > 1 && !ft_memcmp(p->av[1], "-n", 3)))
		write(fd, "\n", 1);
}

int	check_builtins(int fd, t_data *p)
{
	char	*path;
	char	cwd[4097];

	p->ret = 0;
	path = 0;
	if (!ft_memcmp(p->av[0], "echo", 5))
		echo_command(p, fd);
	else if (!ft_memcmp(p->av[0], "pwd", 4))
		ft_putstrs_fd(getcwd(cwd, 4096), "\n", 0, fd);
	else if (!ft_memcmp(p->av[0], "cd", 3))
	{
		path = ft_strdup(p->av[1]);
		cd_command(p);
		free(path);
	}
	else if (!ft_memcmp(p->av[0], "env", 4))
		env_command(p, fd);
	else
		return (127);
	return (p->ret);
}
