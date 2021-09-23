/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:56:23 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/23 18:51:02 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlen_arg(char *s, int *flag)
{
	int	i;

	i = 0;
	if (*flag == 0)
		*flag = 1;
	else
		*flag = 0;
	if (s[i] == '<' || s[i] == '>' || s[i] == '|' || s[i] == '=')
	{
		if (s[i] == '>' && s[i + 1] == '>')
			i = 2;
		else
			i = 1;
	}
	else
	{
		if (*flag == 1)
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
			if (s[i] == '=')
				i++;
		}
		else
		{
			while (s[i] && !ft_isspace(s[i]) && s[i] != '<'
				&& s[i] != '>' && s[i] != '|' && s[i] != '=')
			{
				if (s[i] == '\'' || s[i] == '"')
				{
					i++;
					if (!(s[i]))
						return (i);
				}
				i++;
			}
			if (s[i] == '=')
				i++;
		}
	}
	return (i);
}

int	count_arg(char *str)
{
	int		n;
	int		flag;

	flag = 0;
	n = 0;
	if (!str)
		return (1);
	skip_spaces(&str);
	while (*str)
	{
		n++;
		str += strlen_arg(str, &flag);
		skip_spaces(&str);
	}
	return (n);
}

void	set_arg(char **av, char *str, int ac)
{
	int		i;
	int		len;
	int		flag;

	flag = 0;
	i = 0;
	if (str)
	{
		skip_spaces(&str);
		while (i < ac)
		{
			len = strlen_arg(str, &flag);
			av[i] = ft_strldup(str, len);
			rm_token(&(av[i]));
			i++;
			str += len;
			skip_spaces(&str);
		}
	}
}

void	reset(t_data *p)
{
	p->ac = count_arg(p->str);
	free_matrix(p->av);
	p->av = (char **)ft_calloc(sizeof(char *), (p->ac + 1));
	set_arg(p->av, p->str, p->ac);
}	
