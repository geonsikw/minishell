/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 22:15:36 by jihkwon           #+#    #+#             */
/*   Updated: 2021/09/30 22:19:00 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
