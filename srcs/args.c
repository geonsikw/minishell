/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:02:48 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/17 19:12:47 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_args(t_data *p)
{
	int		i;
	char	**args;

	i = 0;
	while (p->av[i])
		i++;
	args = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (p->av[i])
	{
		args[i] = ft_strdup(p->av[i]);
		i++;
	}
	return (args);
}

int	ft_strlen_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '<' || str[i] == '>' || str[i] == '|')
	{
		if ((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<'))
			i = 2;
		else
			i = 1;
	}
	else
	{
		while (str[i] && !ft_isspace(str[i]) && str[i] != '<'
			&& str[i] != '>' && str[i] != '|')
			i++;
	}
	return (i);
}

void	skip_spaces(char **str)
{
	while (**str == ' ' || (9 <= **str && **str <= 13))
		(*str)++;
}

int	count_args(char *str)
{
	int		n;

	n = 0;
	skip_spaces(&str);
	while (*str)
	{
		n++;
		str += ft_strlen_arg(str);
		skip_spaces(&str);
	}
	return (n);
}

void	set_args(char **av, char *str, int ac)
{
	int		i;
	int		len;

	i = 0;
	skip_spaces(&str);
	while (i < ac)
	{
		len = ft_strlen_arg(str);
		av[i] = ft_strldup(str, len);
		i++;
		str += len;
		skip_spaces(&str);
	}
}
