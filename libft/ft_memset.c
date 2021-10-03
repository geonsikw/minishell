/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 20:05:47 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/03 12:36:05 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int value, size_t count)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)dest;
	while (0 < count--)
		*(tmp++) = (unsigned char)value;
	return (dest);
}
