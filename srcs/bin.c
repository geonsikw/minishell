/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:27:05 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/30 15:09:01 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
*/

int	redirect_in(char *op, char *word, t_data *p)
{
	int		fd;
	int		pfd[2];
	char	*filename;

	if (ft_strcmp(op, "<") == 0)
	{
		filename = expand_redir_filename(word, p->envp, p->ret);
		if (!filename)
			return (-1);
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			ft_putstrs_fd("minishell: ", filename, ": ", 2);
			perror(0);
		}
		free(filename);
		return (fd);
	}
	pipe(pfd);
	write(pfd[1], word, ft_strlen(word));
	close(pfd[1]);
	return (pfd[0]);
}

int	set_fd_in(t_data *p)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (p->av[i])
		if (ft_strcmp(p->av[i], "<") == 0 || ft_strcmp(p->av[i], "<<") == 0)
		{
			if (fd != 0)
				close(fd);
			fd = redirect_in(p->av[i], p->av[i + 1], p);
			if (fd < 0)
				break ;
			i += 2;
		}
		else
			i += 1;
	return (fd);
}

void	exec_bin(int fd, char *path, t_data *p)
{
	char	**args;
	int		fdin;

	args = expand_args(copy_args(p), p->envp, p->ret);
	if (!fork())
	{
		fdin = set_fd_in(p);
		if (fdin < 0)
			exit(p->ret);
		dup2(fdin, 0);
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
		ft_putstrs_fd("iiiibash: ", str, ": No such file or directoryyy\n", 2);
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
	if (ft_strchr(p->av[0], '/'))
	{
		exec_bin(fd, ft_strdup(p->av[0]), p);
		return (p->ret);
	}
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
