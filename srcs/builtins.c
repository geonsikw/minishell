/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:32:40 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/21 20:10:22 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (p->av[i])
	{
		if (check_export_error(p->av, &i))
			p->ret = 1;
		else
		{
			if (!ft_memcmp(p->av[0], "export", 7))
				export_value(p, &i);
			else if (!ft_memcmp(p->av[0], "unset", 6))
				p->envp = unset_command(p, i++);
		}
	}
	return (p->envp);
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
			i++;
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
	char	cwd[4097];

	p->ret = 0;
	if (!ft_memcmp(p->av[0], "echo", 5))
		echo_command(p, fd);
	else if (!ft_memcmp(p->av[0], "pwd", 4))
		ft_putstrs_fd(getcwd(cwd, 4096), "\n", 0, fd);
	else if (!ft_memcmp(p->av[0], "cd", 3))
		cd_command(p);
	else if (!ft_memcmp(p->av[0], "env", 4))
		env_command(p, fd);
	else if (!ft_memcmp(p->av[0], "export", 7)
		|| !ft_memcmp(p->av[0], "unset", 6))
		p->envp = multiple_env(p, fd);
	else if (!ft_memcmp(p->av[0], "exit", 5))
		exit_command(p);
	else
		return (127);
	return (p->ret);
}
