/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:46:17 by gwoo              #+#    #+#             */
/*   Updated: 2021/05/27 14:04:28 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*t;

	if (lst == 0 || f == 0)
		return (NULL);
	if (!(result = ft_lstnew((*f)(lst->content))))
		return (NULL);
	t = result;
	lst = lst->next;
	while (lst)
	{
		if (!(t->next = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		t = t->next;
		lst = lst->next;
	}
	return (result);
}
