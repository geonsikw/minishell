/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 19:44:57 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/12 19:42:55 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t num, size_t size)
{
	unsigned char	*mem;

	if (!(mem = malloc(num * size)))
		return (NULL);
	ft_memset(mem, 0, num * size);
	return ((void *)mem);
}
