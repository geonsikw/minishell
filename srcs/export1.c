/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:17:59 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/02 23:18:01 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset(t_data *p)
{
	int		i;
	int		j;
	int		argc;
	char	**argv;

	j = 1;
	argc = p->ac;
	argv = p->av;
	p->ac = (argc - 1) * 2 + 1;
	p->av = (char **)ft_calloc(sizeof(char *), (p->ac + 1));
	p->av[0] = strdup(argv[0]);
	while (argv[j])
	{
		i = 0;
		while (argv[j][i] && argv[j][i] != '=')
			i++;
		p->av[2 * j - 1] = ft_strldup(argv[j], i + 1);
		if (argv[j][i])
			p->av[2 * j] = ft_strdup(argv[j] + i + 1);
		else
			p->av[2 * j] = ft_strdup(argv[j] + i);
		j++;
	}
	free_matrix(argv);
}

char	**export_command(t_data *p, int fd)
{
	int	i;

	p->ret = 0;
	if (p->ac == 1)
		sort_envp(p->envp, fd, '=');
	reset(p);
	i = 1;
	while (p->av[i])
	{
		if (check_export_error(p->av, &i))
			p->ret = 1;
		else
			export_value(p, &i);
	}
	return (p->envp);
}
