/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 20:03:10 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/02 22:37:34 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	child_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		exit(0);
	}
}

void	ft_addchr(char **str, char c)
{
	char	*aux;

	aux = ft_calloc(sizeof(char), ft_strlen(*str) + 2);
	ft_memcpy(aux, *str, ft_strlen(*str));
	aux[ft_strlen(aux)] = c;
	if (*str)
		free(*str);
	*str = aux;
}
*/

int	ft_putstrs_fd(char *before, char *str, char *after, int fd)
{
	if (before)
		write(fd, before, ft_strlen(before));
	if (str)
		write(fd, str, ft_strlen(str));
	if (after)
		write(fd, after, ft_strlen(after));
	return (1);
}

int	digits_only(char *str)
{
	while (ft_isdigit(*str))
		str++;
	return (!*str);
}

char	*getname(char **word)
{
	int		i;
	char	*name;

	i = 0;
	if (ft_isalpha((*word)[i]))
		while (ft_isalnum((*word)[++i]) || (*word)[i] == '_')
			;
	name = ft_strldup((*word), i);
	*word += i;
	return (name);
}

char	*strjoin_replace(char *s1, char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (join);
}

char	*ft_strtok(char **str, char *delim)
{
	int		i;
	char	*res;

	i = 0;
	while (!ft_strchr(delim, (*str)[i]))
		i++;
	res = ft_strldup(*str, i);
	*str += i;
	return (res);
}
