/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:27:05 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/04 12:18:13 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
*/

void	search_exec(char **paths, char *file, char *argv[], char *envp[])
{
	char	*path;
	char	*lastfound;
	int		err;
	int		i;

	lastfound = 0;
	err = ENOENT;
	i = -1;
	while (paths[++i])
	{
		path = strjoin_path(paths[i], file);
		execve(path, argv, envp);
		if (errno != ENOENT)
		{
			err = errno;
			free(lastfound);
			lastfound = ft_strdup(path);
		}
		free(path);
	}
	errno = err;
	if (err == ENOENT)
		return (ft_putstrs_fd("minishell: ", file, ": command not found\n", 2));
	perror2("minishell", lastfound);
	free(lastfound);
}

void	ft_execvpe(char *path, char *argv[], char *envp[])
{
	char	*path_env;
	char	**paths;

	path_env = get_env(envp, "PATH");
	if (ft_strchr(path, '/') || !path_env || !path_env[0])
	{
		execve(path, argv, envp);
		return (perror2("minishell", path));
	}
	paths = ft_split(path_env, ':');
	search_exec(paths, path, argv, envp);
	free_matrix(paths);
}

int	check_bin(int fdin, int fdout, t_data *p)
{
	if (fork() == 0)
	{
		dup2(fdin, 0);
		dup2(fdout, 1);
		if (fdin != 0)
			close(fdin);
		if (fdout != 1)
			close(fdout);
		ft_execvpe(p->av[0], p->av, p->envp);
		if (errno == ENOENT)
			exit(127);
		exit(126);
	}
	wait(&p->ret);
	p->ret /= 256;
	return (p->ret);
}
