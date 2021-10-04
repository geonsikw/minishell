/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:23:36 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/04 16:38:44 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*expand_split_param(char **word, char *envp[], int exitcode)
{
	char	*param_exp;
	t_list	*list;

	param_exp = expand_param(word, envp, exitcode, 0);
	list = split_to_list(param_exp);
	free(param_exp);
	return (list);
}

t_list	*merge_fieldlist(t_list *fl1, t_list *fl2)
{
	t_list	*last;

	last = ft_lstlast(fl1);
	last->content = merge_field(
			(struct s_field *)fl2->content,
			(struct s_field *)last->content);
	last->next = fl2->next;
	free(fl2);
	return (fl1);
}

void	remove_empty_fields(t_list **fields)
{
	struct s_field	*f;
	t_list			*tmp;

	while (*fields)
	{
		f = (*fields)->content;
		if (!f->wasq && ft_strcmp(f->str, "") == 0)
		{
			tmp = *fields;
			*fields = (*fields)->next;
			ft_lstdelone(tmp, free_field);
		}
		else
			fields = &(*fields)->next;
	}
}

t_list	*expand_word(char *word, char *envp[], int exitcode)
{
	t_list	*fields;

	fields = ft_lstnew(new_field(0, ft_strdup("")));
	while (*word)
	{
		if (isquotechar(*word))
			fields->content = merge_field(
					(struct s_field *)fields->content,
					new_field(1, expand_quote(&word, envp, exitcode)));
		else if (*word == '$')
			fields = merge_fieldlist(
					expand_split_param(&word, envp, exitcode),
					fields);
		else
			fields->content = merge_field(
					(struct s_field *)fields->content,
					new_field(0, ft_strtok(&word, "'\"$")));
	}
	remove_empty_fields(&fields);
	return (fields);
}
