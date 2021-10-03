/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 21:11:16 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/03 15:00:34 by jihkwon          ###   ########.fr       */
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
	free_matrix(p->av);
	p->av = tmp;
	p->ac = j;
}

pid_t	pipe_son(int *flag, int *fds, t_data *p, int pos)
{
	int		i;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sig_nop);
		signal(SIGQUIT, sig_nop);
		if (!flag[0])
			dup2(fds[0], 0);
		if (!flag[1])
			dup2(fds[3], 1);
		i = 0;
		while (i < 4)
			close(fds[i++]);
		set_pipe_args(p, pos);
		check_command(p->str, p);
		free_matrix(p->av);
		exit(p->ret);
	}
	return (pid);
}

void	switch_pipes(int *fds)
{
	close(fds[0]);
	close(fds[1]);
	fds[0] = fds[2];
	fds[1] = fds[3];
	pipe(&fds[2]);
}

int	check_pipe(pid_t *lastpid, int *fds, t_data *p)
{
	int		sons;
	int		flag[2];
	int		i;
	int		j;

	sons = 0;
	flag[0] = 1;
	flag[1] = 0;
	j = 0;
	while (p->av[j])
	{
		i = 0;
		while (p->av[j + i] && ft_memcmp(p->av[j + i], "|", 2))
			i++;
		if (!p->av[j + i])
			flag[1] = 1;
		*lastpid = pipe_son(flag, fds, p, j);
		sons++;
		flag[0] = 0;
		switch_pipes(fds);
		if (!p->av[j + i])
			break ;
		j += i + 1;
	}
	return (sons);
}

void	command_or_pipe(t_data *p)
{
	int		fds[4];
	int		sons;
	int		i;
	pid_t	lastpid;

	i = 0;
	while (p->av[i] && ft_memcmp(p->av[i], "|", 2))
		i++;
	if (!p->av[i])
		p->envp = check_command(p->cmds, p);
	else if (p->cmds)
	{
		pipe(&fds[0]);
		pipe(&fds[2]);
		sons = check_pipe(&lastpid, fds, p);
		waitpid(lastpid, &p->ret, 0);
		while (--sons > 0)
			wait(0);
		p->ret /= 256;
		i = -1;
		while (++i < 4)
			close(fds[i]);
	}
}
