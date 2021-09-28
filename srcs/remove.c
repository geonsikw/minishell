/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:18:17 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/24 00:44:20 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_var(char *a, char *b, char *c, char *d)
{
	free(a);
	free(b);
	free(c);
	free(d);
}

void	free_p(t_data *p)
{
	free(p->str);
	free_matrix(p->envp);
	free_matrix(p->export);
	free_matrix(p->av);
	free(p->cmds);
	free(p);
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

void	rm_char(char **str, int j)
{
	char	*bef;
	char	*aux;

	bef = ft_strldup(*str, j);
	aux = ft_strdup(*str + j + 1);
	free(*str);
	*str = ft_strjoin(bef, aux);
	free(aux);
	free(bef);
}

void	rm_token(char **arg)
{
	int		i;

	i = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\'')
		{
			rm_char(arg, i);
			i += ft_strlen_char(*arg + i, '\'');
			rm_char(arg, i);
		}
		else if ((*arg)[i] == '"')
		{
			rm_char(arg, i);
			i += ft_strlen_char(*arg + i, '\"');
			rm_char(arg, i);
		}
		else
			i++;
	}
}
