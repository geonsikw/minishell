/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 21:31:45 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/02 23:14:50 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	redirect(t_data *p, int i, int fd)
{
	int		ret;
	char	c;
	char	*filename;

	while (p->av[i])
	{
		if (!ft_memcmp(p->av[i], ">", 2))
			fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
		else if (!ft_memcmp(p->av[i], ">>", 3))
		{
			fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0666);
			ret = 0;
			while ((ret = read(fd, &c, 1)))
			{
				if (ret == -1)
				{
					write(2, "Couldn't read file\n", 19);
					break ;
				}
			}
		}
		i++;
		if (p->av[i] && (!ft_memcmp(p->av[i], ">>", 3)
				|| !ft_memcmp(p->av[i], ">", 2)))
			close(fd);
	}
	return (fd);
}

int	set_fd(t_data *p)
{
	int		i;
	int		fd;

	i = 0;
	fd = 1;
	while (p->av[i] && ft_memcmp(p->av[i], ">", 2)
		&& ft_memcmp(p->av[i], ">>", 3))
		i++;
	if (!p->av[i])
		return (1);
	return (redirect(p, i, fd));
}

char	**check_command(char *str, t_data *p)
{
	int		fd;

	(void)str;
	if (p->av[0] && *(p->av[0]))
	{
		fd = set_fd_out(p);
		if (fd < 0)
			return (p->envp);
		copy_args1(p);
		if (check_builtins(fd, p) < 0 && check_bin(fd, p) == 127)
		{
			ft_putstrs_fd("minishell: ", p->av[0], ": command not found.\n", 2);
			p->ret = 127;
		}
		if (fd != 1)
			close(fd);
	}
	return (p->envp);
}
*/

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
