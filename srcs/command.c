/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 21:31:45 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/30 14:56:55 by jihkwon          ###   ########.fr       */
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
*/

int	redirect_out(char *op, char *word, t_data *p)
{
	int		fd;
	char	*filename;

	filename = expand_redir_filename(word, p->envp, p->ret);
	if (!filename)
		return (-1);
	if (ft_strcmp(op, ">") == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		ft_putstrs_fd("minishell: ", filename, ": ", 2);
		perror(0);
	}
	free(filename);
	return (fd);
}

int	set_fd_out(t_data *p)
{
	int	i;
	int	fd;

	i = 0;
	fd = 1;
	while (p->av[i])
		if (ft_strcmp(p->av[i], ">") == 0 || ft_strcmp(p->av[i], ">>") == 0)
		{
			if (fd != 1)
				close(fd);
			fd = redirect_out(p->av[i], p->av[i + 1], p);
			if (fd < 0)
				break ;
			i += 2;
		}
		else
			i += 1;
	return (fd);
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
