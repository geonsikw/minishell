/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 21:31:45 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/03 13:01:50 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redir(t_data *p)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (++i < p->ac)
	{
		if (!ft_memcmp(p->av[i], ">", 2)
			|| !ft_memcmp(p->av[i], ">>", 3)
			|| !ft_memcmp(p->av[i], "<", 2)
			|| !ft_memcmp(p->av[i], "<<", 3))
		{
			count++;
			i++;
		}
	}
	return (count);
}

void	copy_args1(t_data *p)
{
	int		i;
	int		j;
	char	**args;

	p->ac -= count_redir(p) * 2;
	args = (char **)ft_calloc(sizeof(char *), p->ac + 1);
	i = 0;
	j = 0;
	while (j < p->ac)
	{
		if (!ft_memcmp(p->av[i], ">", 2)
			|| !ft_memcmp(p->av[i], ">>", 3)
			|| !ft_memcmp(p->av[i], "<", 2)
			|| !ft_memcmp(p->av[i], "<<", 3))
			i += 2;
		else
			args[j++] = ft_strdup(p->av[i++]);
	}
	free_matrix(p->av);
	p->av = args;
}

int	check_builtins(int fd, t_data *p)
{
	char	cwd[4097];

	if (!ft_memcmp(p->av[0], "echo", 5))
		echo_command(p, fd);
	else if (!ft_memcmp(p->av[0], "pwd", 4))
	{
		p->ret = 0;
		ft_putstrs_fd(getcwd(cwd, 4096), "\n", 0, fd);
	}
	else if (!ft_memcmp(p->av[0], "cd", 3))
		cd_command(p);
	else if (!ft_memcmp(p->av[0], "env", 4))
		env_command(p, fd);
	else if (!ft_memcmp(p->av[0], "export", 7))
		p->envp = export_command(p, fd);
	else if (!ft_memcmp(p->av[0], "unset", 6))
		p->envp = unset_command(p, fd);
	else if (!ft_memcmp(p->av[0], "exit", 5))
		exit_command(p);
	else
		return (-1);
	return (0);
}

char	**check_command(char *str, t_data *p)
{
	int	fdin;
	int	fdout;

	(void)str;
	if (!p->av[0] || !*(p->av[0]))
		return (p->envp);
	fdin = set_fd_in(p);
	fdout = set_fd_out(p);
	if (fdin < 0 || fdout < 0)
	{
		p->ret = 1;
		return (p->envp);
	}
	copy_args1(p);
	expand_args(p);
	if (check_builtins(fdout, p) < 0 && check_bin(fdin, fdout, p) == 127)
	{
		ft_putstrs_fd("minishell: ", p->av[0], ": command not found\n", 2);
		p->ret = 127;
	}
	if (fdin != 0)
		close (fdin);
	if (fdout != 1)
		close (fdout);
	return (p->envp);
}
