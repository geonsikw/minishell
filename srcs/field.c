/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:18:18 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/02 23:18:30 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_field	*new_field(int wasq, char *str)
{
	struct s_field	*new;

	new = malloc(sizeof(struct s_field));
	new->wasq = wasq;
	new->str = str;
	return (new);
}

struct s_field	*merge_field(struct s_field *f1, struct s_field *f2)
{
	struct s_field	*new;

	new = new_field(f1->wasq | f2->wasq, ft_strjoin(f1->str, f2->str));
	free_field(f1);
	free_field(f2);
	return (new);
}

void	free_field(void *f)
{
	free(((struct s_field *)f)->str);
	free(f);
}
