/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 22:38:11 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/16 04:30:33 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_char(char **str, int j)
{
	char	*bef;
	char	*aft;

	bef = ft_strldup(*str, j);
	aft = ft_strdup(*str + j + 1);
	free(*str);
	*str = ft_strjoin(bef, aft);
	free(aft);
	free(bef);
}

int	ft_strlen_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	ft_addchr(char **str, char c)
{
	char	*tmp;

	tmp = ft_calloc(sizeof(char), ft_strlen(*str) + 2);
	ft_memcpy(tmp, *str, ft_strlen(*str));
	tmp[ft_strlen(tmp)] = c;
	if (*str)
		free(*str);
	*str = tmp;
}
