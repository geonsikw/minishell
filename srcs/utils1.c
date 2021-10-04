/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:22:49 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/04 11:16:46 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isopchar(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	isquotechar(char c)
{
	return (c == '"' || c == '\'');
}

int	iswordchar(char c)
{
	return (c && !ft_isblank(c) && !isopchar(c));
}

char	*strjoin_path(char *dir, char *file)
{
	int		dlen;
	char	*tmp;
	char	*res;

	dlen = ft_strlen(dir);
	if (dlen > 0 && dir[dlen - 1] == '/')
		return (ft_strjoin(dir, file));
	tmp = ft_strjoin(dir, "/");
	res = ft_strjoin(tmp, file);
	free(tmp);
	return (res);
}
