/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:25:33 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/02 23:25:36 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_param(char **word, char *envp[], int exitcode)
{
	char	*value;
	char	*name;

	++*word;
	if (ft_isalnum(**word))
	{
		name = getname(word);
		value = get_env(envp, name);
		if (!value)
			value = "";
		free(name);
		return (ft_strdup(value));
	}
	if (isquotechar(**word))
		return (ft_strdup(""));
	if (**word == '?')
	{
		++*word;
		return (ft_itoa(exitcode));
	}
	return (ft_strdup("$"));
}

char	*expand_quote(char **word, char *envp[], int exitcode)
{
	char	*res;

	if (*(*word)++ == '\'')
		res = ft_strtok(word, "'");
	else
	{
		res = ft_strdup("");
		while (**word != '"')
		{
			if (**word == '$')
				res = strjoin_replace(res, expand_param(word, envp, exitcode));
			else
				res = strjoin_replace(res, ft_strtok(word, "\"$"));
		}
	}
	++*word;
	return (res);
}

t_list	*split_to_list(char *str)
{
	t_list	*list;

	list = ft_lstnew(new_field(0, ft_strtok(&str, " \t\n")));
	while (*str)
	{
		while (ft_isblank(*str) || *str == '\n')
			str++;
		ft_lstadd_front(
			&list, ft_lstnew(new_field(0, ft_strtok(&str, " \t\n"))));
	}
	return (list);
}
