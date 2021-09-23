/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:02:48 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/22 20:26:02 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_args(t_data *p)
{
	int		i;
	char	**args;

	i = 0;
	while (p->av[i] && ft_memcmp(p->av[i], "<", 2))
		i++;
	args = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (p->av[i] && ft_memcmp(p->av[i], "<", 2))
	{
		args[i] = ft_strdup(p->av[i]);
		i++;
	}
	return (args);
}

int	ft_strlen_arg(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '<' || s[i] == '>' || s[i] == '|')
	{
		if (s[i] == '>' && s[i + 1] == '>')
			i = 2;
		else
			i = 1;
	}
	else
	{
		while (s[i] && !ft_isspace(s[i]) && s[i] != '<'
			&& s[i] != '>' && s[i] != '|')
		{
			if (s[i] == '\'' || s[i] == '"')
			{
				i++;
				if (!(s[i]))
					return (i);
			}
			i++;
		}
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
	if (!str)
		return (1);
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
	if (str)
	{
		skip_spaces(&str);
		while (i < ac)
		{
			len = ft_strlen_arg(str);
			av[i] = ft_strldup(str, len);
			rm_token(&(av[i]));
			i++;
			str += len;
			skip_spaces(&str);
		}
	}
}
