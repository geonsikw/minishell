/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:27:05 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/21 21:08:01 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_in(char **av)
{
	int		fd;
	int		i;

	i = 0;
	while (av[i] && ft_memcmp(av[i], "<", 2))
		i++;
	if (av[i])
	{
		fd = open(av[i + 1], O_RDONLY, 0666);
		if (fd < 0)
		{
			ft_putstr_fd("Couldn't read from file.\n", 2);
			return ;
		}
		dup2(fd, 0);
		close(fd);
	}
}

void	exec_bin(int fd, char *path, t_data *p)
{
	char	**args;

	args = copy_args(p);
	if (!fork())
	{
		set_in(p->av);
		if (fd > 1)
			dup2(fd, 1);
		if ((execve(path, args, p->envp)) && errno == EACCES)
		{
			p->ret = 126;
			ft_putstrs_fd("bash: ", p->av[0], ": ", 2);
			ft_putstrs_fd(strerror(errno), "\n", 0, 2);
		}
		exit(p->ret);
	}
	wait(&p->ret);
	p->ret /= 256;
	free(path);
	free_matrix(args);
}

char	**split_path(t_data *p, char *str)
{
	char	*path;
	char	**paths;

	path = get_env(p->envp, "PATH");
	if (path)
		paths = ft_split(path, ':');
	else
	{
		ft_putstrs_fd("bash: ", str, ": No such file or directory\n", 2);
		p->ret = 127;
		return (NULL);
	}
	return (paths);
}

char	*search_bin(char *str, DIR **dir, struct dirent **d, t_data *p)
{
	char		**paths;
	char		*path;
	int			i;

	paths = split_path(p, str);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		*dir = opendir(paths[i]);
		while ((*dir) && errno != EACCES && (*d = readdir(*dir)))
		{
			if (!ft_memcmp(str, (*d)->d_name, ft_strlen(str) + 1))
			{
				path = ft_strjoin(paths[i], "/");
				free_matrix(paths);
				return (path);
			}
		}
		closedir(*dir);
	}
	free_matrix(paths);
	return (NULL);
}

int	check_bin(int fd, t_data *p)
{
	DIR				*dir;
	struct dirent	*d;
	char			*pre_path;
	char			*path;

	p->ret = 127;
	pre_path = search_bin(p->av[0], &dir, &d, p);
	if (pre_path)
	{
		path = ft_strjoin(pre_path, d->d_name);
		exec_bin(fd, path, p);
		closedir(dir);
	}
	free(pre_path);
	return (p->ret);
}
