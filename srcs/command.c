/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 21:31:45 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/21 21:07:11 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect(t_data *p, int i, int fd)
{
	int		ret;
	char	c;

	while (p->av[i])
	{
		if (!ft_memcmp(p->av[i], ">", 2))
			fd = open(p->av[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
		else if (!ft_memcmp(p->av[i], ">>", 3))
		{
			fd = open(p->av[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
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

int	count_redir(t_data *p)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (++i < p->ac)
	{
		if (!ft_memcmp(p->av[i], ">", 2) || !ft_memcmp(p->av[i], ">>", 3))
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
		if (!ft_memcmp(p->av[i], ">", 2) || !ft_memcmp(p->av[i], ">>", 3))
			i += 2;
		else
			args[j++] = ft_strdup(p->av[i++]);
	}
	free_matrix(p->av);
	p->av = args;
}

char	**check_command(char *str, t_data *p)
{
	int		fd;

	if (p->av[0] && *(p->av[0]))
	{
		fd = set_fd(p);
		copy_args1(p);
		p->ret = check_builtins(fd, p);
		if (p->ret == 127 && check_bin(fd, p) == 127)
		{
			ft_putstrs_fd(0, str, ": command not found.\n", 2);
			p->ret = 127;
		}
		if (fd != 1)
			close(fd);
	}
	return (p->envp);
}
