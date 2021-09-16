/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:06:45 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/16 04:19:36 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export_command(t_data *p, int j)
{
	int		i;
	char	**cpy;

	i = 0;
	while (p->envp[i] && ft_memcmp(p->envp[i],
			p->av[j], ft_strlen(p->av[j])))
		i++;
	cpy = p->envp;
	free(p->envp[i]);
	p->envp[i] = ft_strjoin(p->av[j], p->av[j + 1]);
	return (cpy);
}

void	change_dir(char *path, t_data *p)
{
	char		cwd[4097];

	if (chdir(path) == 0)
	{
		p->ac = 3;
		free_matrix(p->av);
		p->av = (char **)ft_calloc(sizeof(char *), 3);
		p->av[0] = ft_strdup("PWD=");
		p->av[1] = ft_strdup(getcwd(cwd, 4096));
		p->envp = export_command(p, 0);
	}
	else
		ft_putstrs_fd("bash: cd: ", p->av[1], ": ", 2);
}

void	cd_command(t_data *p)
{
	char	*path;

	errno = 0;
	if (p->ac <= 2)
	{
		path = p->av[1];
		change_dir(path, p);
		if (errno > 0)
		{
			ft_putstrs_fd(strerror(errno), "\n", 0, 2);
			p->ret = 1;
		}
	}
	else
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		p->ret = 1;
	}
	errno = 0;
}
