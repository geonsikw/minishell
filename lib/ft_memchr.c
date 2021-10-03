/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:10:15 by gwoo              #+#    #+#             */
/*   Updated: 2021/05/27 15:50:27 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)b == (unsigned char)c)
			return ((void *)b);
		b++;
	}
	return (0);
}
