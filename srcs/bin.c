/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:27:05 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/17 19:00:09 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_bin(int fd, char *path, t_data *p)
{
	char	**args;

	args = copy_args(p);
	if (!fork())
	{
		if (fd > 1)
			dup2(fd, 1);
		execve(path, args, p->envp);
		exit(p->ret);
	}
	wait(&p->ret);
	free(path);
	free_matrix(args);
}

char	**split_path(t_data *p)
{
	char	*path;
	char	**paths;

	path = get_env(p->envp, "PATH");
	paths = ft_split(path, ':');
	return (paths);
}

char	*search_bin(char *str, DIR **dir, struct dirent **d, t_data *p)
{
	char		**paths;
	char		*path;
	int			i;

	paths = split_path(p);
	i = -1;
	while (paths[++i])
	{
		*dir = opendir(paths[i]);
		while ((*dir) && (*d = readdir(*dir)))
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
