/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:15:44 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/02 23:15:50 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**update_envp(t_data *p, int j)
{
	int		i;
	char	**cpy;

	i = 0;
	while (p->envp[i] && ft_memcmp(p->envp[i],
			p->av[j], ft_strlen(p->av[j])))
		i++;
	if (!p->envp[i])
	{
		cpy = copy_env(p->envp, 1);
		cpy[i] = ft_strjoin(p->av[j], p->av[j + 1]);
		free_matrix(p->envp);
	}
	else
	{
		cpy = p->envp;
		free(p->envp[i]);
		p->envp[i] = ft_strjoin(p->av[j], p->av[j + 1]);
	}
	return (cpy);
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
