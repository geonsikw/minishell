/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 21:06:44 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/23 17:24:20 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_errno(t_data *p, char *str)
{
	if (errno == ENOENT || errno == EACCES)
	{
		ft_putstrs_fd("bash: ", str, ": ", 2);
		ft_putstrs_fd(strerror(errno), "\n", 0, 2);
		p->ret = 126;
		if (errno == ENOENT)
			p->ret = 127;
		return (1);
	}
	return (0);
}

void	check_type(t_data *p, char *str, char *path)
{
	DIR			*dir;
	int			fd;
	char		*cmds;

	if (check_errno(p, str))
		return ;
	else if (!(dir = opendir(path)))
	{
		fd = open(path, O_RDONLY, 0666);
		free(p->str);
		while (gnl(fd, &(p->str)))
		{
			cmds = p->cmds;
			parser(p);
			p->cmds = cmds;
		}
		close(fd);
	}
	else
	{
		ft_putstrs_fd("-bash: ", str, ": Is a directory\n", 2);
		p->ret = 126;
		closedir(dir);
	}
}

void	set_filename(int len, char **new, char *str)
{
	int		i;
	char	*filename;
	char	*aux;

	i = 0;
	while (!ft_memcmp(str + i, "../", 3))
	{
		while (len-- > 0)
		{
			if (*(*new + len) == '/')
				break ;
		}
		i += 3;
	}
	filename = ft_strdup(str + i);
	aux = ft_strldup(*new, len);
	free(*new);
	*new = ft_strjoin(aux, "/");
	free(aux);
	aux = ft_strjoin(*new, filename);
	free(*new);
	*new = aux;
	free(filename);
}

void	set_path(char *str, char **path)
{
	int		len;
	char	*new;

	new = ft_strdup(*path);
	len = ft_strlen(*path);
	if (!ft_memcmp(str, "/", 1))
		*path = ft_strdup(str);
	else
	{
		set_filename(len, &new, str);
		*path = new;
		return ;
	}
	free(new);
}

void	excutable(t_data *p)
{
	char	buff[4097];
	char	*path;
	char	*start;

	start = p->av[0];
	if (ft_memcmp(p->av[0], "/", 1))
		if (!ft_memcmp(p->av[0], "./", 2))
			p->av[0] += 2;
	path = getcwd(buff, 4096);
	set_path(p->av[0], &path);
	if (!fork())
	{
		signal(SIGINT, child_sig_handler);
		if (execve(path, p->av, p->envp))
			check_type(p, start, path);
		exit(p->ret);
	}
	else
		wait(&p->ret);
	p->ret /= 256;
	free(path);
	p->av[0] = start;
}
