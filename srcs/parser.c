/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 20:02:38 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/19 16:12:44 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_env(int i, int brace, char **str, t_data *p)
{
	int		len;
	char	*bef;
	char	*aft;
	char	*env;
	char	*aux;

	if ((*str)[i + 1] == '{')
		brace = 1;
	else
		brace = 0;
	if (ft_strlen_char(*str + i + 1, ':') < ft_strlen_env(*str + i + 1))
		len = ft_strlen_char(*str + i + 1, ':') + 1;
	else
		len = ft_strlen_env(*str + i + 1) + 1 + brace;
	bef = ft_strldup(*str, i);
	aux = ft_strldup(*str + i + 1 + brace, len - 1 - brace * 2);
	if (!ft_memcmp(aux, "?", 2))
		env = ft_itoa(p->ret);
	else
		env = 0;
	aft = ft_strdup(*str + i + len);
	if (!env)
		env = ft_strdup(get_env(p->envp, aux));
	free(aux);
	len = ft_strlen(env);
	aux = ft_strjoin(bef, env);
	free(bef);
	free(env);
	free(*str);
	*str = ft_strjoin(aux, aft);
	free(aux);
	free(aft);
	return (len);
}

int	check_quotes(char **str, int *i, int *f)
{
	char	quote;
	int		j;

	if (*f == 0)
		*f = 1;
	else if (*f == 1)
		*f = 0;
	j = *i;
	quote = (*str)[*i];
	(*i)++;
	while ((*str)[*i] && ((*str)[*i] != quote))
		(*i)++;
	if (!(*str)[*i] && *f == 1)
	{
		ft_putstr_fd("Syntax error : Non finished quotes\n", 2);
		if (quote == '"' || quote == '\'')
		{
			*i = j;
			return (0);
		}
		return (1);
	}
	if (quote == '"')
		*i = j;
	return (0);
}

int	check_env(char **str, t_data *p)
{
	int	i;
	int	brace;
	int	f;

	i = 0;
	brace = 0;
	f = 0;
	while ((*str) && (*str)[i])
	{
		if (((*str)[i] == '\'' || (*str)[i] == '"')
			&& check_quotes(str, &i, &f))
			return (1);
		if ((*str)[i] == '$' && !(!(*str)[i + 1] ||
		ft_isspace((*str)[i + 1]) || (*str)[i + 1] == '\'' ||
		(*str)[i + 1] == '"' || (*str)[i + 1] == '/'))
			i += change_env(i, brace, str, p) - 1;
		i++;
	}
	return (0);
}

char	*copy_str(char *s)
{
	char	*mat;

	if (!s)
		return (NULL);
	mat = (char *)ft_calloc(sizeof(char), 2);
	mat = ft_strldup(s, ft_strlen(s));
	return (mat);
}

void	parser(t_data *p)
{
	p->cmds = copy_str(p->str);
	check_env(&(p->cmds), p);
	p->ac = count_args(p->cmds);
	p->av = (char **)ft_calloc(sizeof(char *), (p->ac + 1));
	set_args(p->av, p->cmds, p->ac);
	command_or_pipe(p);
	free_matrix(p->av);
	free(p->str);
	p->str = 0;
	free(p->cmds);
}
