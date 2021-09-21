/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 20:02:38 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/21 21:13:58 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_join(char *dest, char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;

	free(dest);
	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
	{
		if (!(s1))
			return (ft_strdup(s2));
		else
			return (ft_strdup(s1));
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, s1_len + 1);
	ft_strlcat(dest + (s1_len), s2, s2_len + 1);
	return (dest);
}

int	change_env(int i, int braces, char **str, t_data *param)
{
	int		len;
	char	*bef;
	char	*aft;
	char	*env;
	char	*aux;

	if ((*str)[i + 1] == '{')
		braces = 1;
	len = ft_strlen_env(*str + i + 1) + 1 + braces;
	if (ft_strlen_char(*str + i + 1, ':') < ft_strlen_env(*str + i + 1))
		len = ft_strlen_char(*str + i + 1, ':') + 1;
	bef = ft_strldup(*str, i);
	aux = ft_strldup(*str + i + 1 + braces, len - 1 - braces * 2);
	env = 0;
	if (!ft_memcmp(aux, "?", 2))
		env = ft_itoa(param->ret);
	aft = ft_strdup(*str + i + len);
	if (!env)
		env = ft_strdup(get_env(param->envp, aux));
	len = ft_strlen(env);
	aux = free_join(aux, bef, env);
	*str = free_join(*str, aux, aft);
	free_var(aux, aft, bef, env);
	return (len);
}

void	check_quotes(char **str, int *i, int *f)
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
		*i = j;
	}
	if (quote == '"')
		*i = j;
}

int	check_env(char **str, t_data *p)
{
	int	i;
	int	brace;
	int	f;

	i = 0;
	f = 0;
	while ((*str) && (*str)[i])
	{
		brace = 0;
		if (((*str)[i] == '\'' || (*str)[i] == '"'))
			 check_quotes(str, &i, &f);
		if ((*str)[i] == '$' && !(!(*str)[i + 1] ||
		ft_isspace((*str)[i + 1]) || (*str)[i + 1] == '\'' ||
		(*str)[i + 1] == '"' || (*str)[i + 1] == '/'))
			i += change_env(i, brace, str, p) - 1;
		i++;
	}
	return (0);
}

void	parser(t_data *p)
{
	if (!p->str)
		p->cmds = NULL;
	else
		p->cmds = ft_strldup(p->str, ft_strlen(p->str));
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
