/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:24:41 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/19 11:25:55 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**erase_env(char **envp, int i)
{
	int		j;
	int		len;
	char	**cpy;

	len = 0;
	while (envp[len])
		len++;
	cpy = (char **)ft_calloc(sizeof(char *), len);
	if (!cpy)
		return (NULL);
	j = -1;
	while (++j < i)
		cpy[j] = ft_strdup(envp[j]);
	i++;
	while (envp[i])
		cpy[j++] = ft_strdup(envp[i++]);
	free_matrix(envp);
	return (cpy);
}

char	**unset_command(t_data *p, int j)
{
	int		i;
	int		len;
	char	*env;
	char	**cpy;

	if (p->ac < 2)
		return (p->envp);
	len = strlen(p->av[j]);
	env = ft_strjoin(p->av[j], "=");
	i = 0;
	while (p->envp[i] && ft_memcmp(env, p->envp[i], len + 1))
		i++;
	if (p->envp[i])
		cpy = erase_env(p->envp, i);
	else
		cpy = p->envp;
	free(env);
	return (cpy);
}
