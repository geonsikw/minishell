/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 20:58:35 by gwoo              #+#    #+#             */
/*   Updated: 2021/05/27 16:22:34 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *last;

	last = *lst;
	if (lst == NULL && new == NULL)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
