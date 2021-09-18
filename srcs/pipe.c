/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 21:11:16 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/17 19:17:00 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipe_args(t_data *p, int i)
{
	char	**tmp;
	int		j;
	int		k;

	j = 0;
	while (p->av[i + j] && ft_memcmp(p->av[i + j], "|", 2))
		j++;
	tmp = (char **)ft_calloc(sizeof(char *), j + 1);
	k = -1;
	while (++k < j)
		tmp[k] = ft_strdup(p->av[i + k]);
	p->av = tmp;
	p->ac = j;
}

void	pipe_son(int *flag, int *fds, t_data *p, int pos)
{
	int		i;
	int		ac;
	char	**av;

	if (!fork())
	{
		if (!flag[0])
			dup2(fds[0], 0);
		if (!flag[1])
			dup2(fds[3], 1);
		i = 0;
		while (i < 4)
			close(fds[i++]);
		ac = p->ac;
		av = p->av;
		set_pipe_args(p, pos);
		check_command(p->str, p);
		free_matrix(p->av);
		p->ac = ac;
		p->av = av;
		exit(p->ret);
	}
}

void	switch_pipes(int *fds)
{
	close(fds[0]);
	close(fds[1]);
	fds[0] = fds[2];
	fds[1] = fds[3];
	pipe(&fds[2]);
}

int	check_pipe(int *fds, t_data *p)
{
	int		sons;
	int		*flag;
	int		i;
	int		j;

	sons = 0;
	flag = (int *)calloc(sizeof(int), 2);
	flag[0] = 1;
	j = 0;
	while (p->av[j])
	{
		i = 0;
		while (p->av[j + i] && ft_memcmp(p->av[j + i], "|", 2))
			i++;
		if (!p->av[j + i])
			flag[1] = 1;
		pipe_son(flag, fds, p, j);
		sons++;
		flag[0] = 0;
		switch_pipes(fds);
		if (!p->av[j + i])
			j += i;
		else
			j += i + 1;
	}
	free(flag);
	return (sons);
}

void	command_or_pipe(t_data *p)
{
	int	fds[4];
	int	sons;
	int	i;

	i = 0;
	while (p->av[i] && ft_memcmp(p->av[i], "|", 2))
		i++;
	if (!p->av[i])
		p->envp = check_command(p->cmds, p);
	else if (p->cmds[0])
	{
		pipe(&fds[0]);
		pipe(&fds[2]);
		sons = check_pipe(fds, p);
		while (sons-- > 0)
			wait(&p->ret);
		p->ret /= 256;
		i = -1;
		while (++i < 4)
			close(fds[i]);
	}
}
