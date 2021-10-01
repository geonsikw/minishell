/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 20:03:10 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/01 00:10:22 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_env(char **envp, char *env)
{
	int		i;
	int		len;
	char	*tmp;

	env = ft_strjoin(env, "=");
	len = strlen(env);
	i = 0;
	while (envp[i] && ft_memcmp(env, envp[i], len))
		i++;
	if (envp[i])
		tmp = envp[i] + len;
	else
		tmp = 0;
	free(env);
	return (tmp);
}

char	**copy_env(char **envp, int add)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	while (envp[len])
		len++;
	cpy = (char **)ft_calloc(sizeof(char *), (len + add + 1));
	if (!cpy)
		return (NULL);
	i = -1;
	while (++i < len)
		cpy[i] = ft_strdup(envp[i]);
	return (cpy);
}

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
