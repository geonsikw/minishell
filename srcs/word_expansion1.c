/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:12:32 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/02 23:12:40 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_redir_filename(char *word, char *envp[], int exitcode)
{
	t_list	*list;
	char	*res;

	res = 0;
	list = expand_word(word, envp, exitcode);
	if (ft_lstsize(list) == 1)
		res = ft_strdup(((struct s_field *)list->content)->str);
	else
		ft_putstrs_fd("minishell: ", word, ": ambiguous redirect\n", 2);
	ft_lstclear(&list, free_field);
	return (res);
}

char	*remove_quotes(char *word)
{
	char	*res;

	res = ft_strdup("");
	while (*word)
	{
		if (*word == '\'')
		{
			word++;
			res = strjoin_replace(res, ft_strtok(&word, "'"));
		}
		else if (*word == '"')
		{
			word++;
			res = strjoin_replace(res, ft_strtok(&word, "\""));
		}
		else
			res = strjoin_replace(res, ft_strtok(&word, "'\""));
	}
	return (res);
}

static char	**get_array_from_list(t_list **list, int size)
{
	t_list	*node;
	char	**arr;

	node = *list;
	arr = malloc(sizeof(char *) * (size + 1));
	arr[size] = 0;
	while (--size >= 0)
	{
		arr[size] = ((struct s_field *)node->content)->str;
		node = node->next;
	}
	ft_lstclear(list, free);
	return (arr);
}

void	expand_args(t_data *p)
{
	t_list	*arglist;
	int		i;

	arglist = 0;
	i = -1;
	while (p->av[++i])
		arglist = ft_lstjoin(
				expand_word(p->av[i], p->envp, p->ret),
				arglist);
	free_matrix(p->av);
	p->ac = ft_lstsize(arglist);
	p->av = get_array_from_list(&arglist, p->ac);
}
