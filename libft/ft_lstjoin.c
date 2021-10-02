/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 22:22:13 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/02 22:22:19 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstjoin(t_list *lst1, t_list *lst2)
{
	t_list	**end;

	end = &lst1;
	while (*end)
		end = &(*end)->next;
	*end = lst2;
	return (lst1);
}
