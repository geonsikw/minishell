/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:27:05 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/03 12:56:23 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_bin(int fdin, int fdout, char *path, t_data *p)
{
	if (!fork())
	{
		dup2(fdin, 0);
		dup2(fdout, 1);
		if ((execve(path, p->av, p->envp)) && errno == EACCES)
		{
			p->ret = 126;
			ft_putstrs_fd("minishell: ", p->av[0], ": ", 2);
			ft_putstrs_fd(strerror(errno), "\n", 0, 2);
		}
		exit(p->ret);
	}
	wait(&p->ret);
	p->ret /= 256;
	free(path);
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
		ft_putstrs_fd("minishell: ", str, ": No such file or directory\n", 2);
		p->ret = 127;
		return (NULL);
	}
	return (paths);
}

char	*search_bin(int i, DIR **dir, struct dirent **d, t_data *p)
{
	char		**paths;
	char		*path;

	paths = split_path(p, p->av[0]);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		*dir = opendir(paths[i]);
		*d = readdir(*dir);
		while ((*dir) && errno != EACCES && *d)
		{
			if (!ft_memcmp(p->av[0], (*d)->d_name, ft_strlen(p->av[0]) + 1))
			{
				path = ft_strjoin(paths[i], "/");
				free_matrix(paths);
				return (path);
			}
			*d = readdir(*dir);
		}
		closedir(*dir);
	}
	free_matrix(paths);
	return (NULL);
}

int	check_bin(int fdin, int fdout, t_data *p)
{
	DIR				*dir;
	struct dirent	*d;
	char			*pre_path;
	char			*path;
	int				i;

	i = -1;
	p->ret = 127;
	if (ft_strchr(p->av[0], '/'))
	{
		exec_bin(fdin, fdout, ft_strdup(p->av[0]), p);
		return (p->ret);
	}
	pre_path = search_bin(i, &dir, &d, p);
	if (pre_path)
	{
		path = ft_strjoin(pre_path, d->d_name);
		exec_bin(fdin, fdout, path, p);
		closedir(dir);
	}
	free(pre_path);
	return (p->ret);
}
