/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:23:51 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/21 20:42:20 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_export(t_data *p, char **aux, int *i, int j)
{
	aux[j] = ft_strdup(p->av[*i]);
	aux[j + 1] = 0;
	free_matrix(p->export);
	p->export = aux;
}

void	export_value(t_data *p, int *i)
{
	char	**aux;
	int		j;

	if (!ft_strchr(p->av[*i], '='))
	{
		j = 0;
		while (p->export[j] && ft_memcmp(p->export[j],
				p->av[*i], ft_strlen(p->av[*i])))
			j++;
		if (!p->export[j])
		{
			aux = copy_env(p->export, 1);
			set_export(p, aux, i, j);
		}
		(*i)++;
	}
	else
	{
		p->envp = export_command(p, *i);
		if (p->av[*i + 1])
			*i += 2;
		else
			*i += 1;
	}
}

int	check_export_error(char **av, int *i)
{
	int	j;

	j = 0;
	while (ft_isalnum(av[*i][j]) || av[*i][j] == '_' ||
			av[*i][j] == '#' || av[*i][j] == '=' || av[*i][j] == '$')
		j++;
	if (ft_isdigit(av[*i][0]) || av[*i][j])
	{
		if (ft_strchr(av[*i], '='))
		{
			ft_putstrs_fd("bash: ", av[0], ": `", 2);
			ft_putstrs_fd(av[*i], av[(*i) + 1],
				"': not a valid identifier\n", 2);
			(*i)++;
		}
		else
		{
			ft_putstrs_fd("bash: ", av[0], ": `", 2);
			ft_putstrs_fd(av[*i], "': not a valid identifier\n", 0, 2);
		}
		(*i)++;
		return (1);
	}
	return (0);
}

void	put_envp(char **aux, int fd)
{
	int	i;

	i = -1;
	while (aux[++i])
	{
		ft_putstrlen_fd(aux[i], ft_strlen_char(aux[i], '=') + 1, fd);
		if (ft_strchr(aux[i], '='))
			ft_putstr_fd(ft_strchr(aux[i], '=') + 1, fd);
		write(fd, "\n", 1);
	}
	free_matrix(aux);
}

void	sort_envp(char **envp, int fd, char c)
{
	int		i;
	int		len;
	char	**aux;
	char	*tmp;

	aux = copy_env(envp, 0);
	i = 0;
	while (aux[i] && aux[i + 1])
	{
		if (ft_strlen_char(aux[i], c) > ft_strlen_char(aux[i + 1], c))
			len = ft_strlen_char(aux[i], c);
		else
			len = ft_strlen_char(aux[i + 1], c);
		if (ft_memcmp(aux[i], aux[i + 1], len) > 0)
		{
			tmp = aux[i];
			aux[i] = aux[i + 1];
			aux[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	put_envp(aux, fd);
}
