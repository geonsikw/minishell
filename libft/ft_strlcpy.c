/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:15:43 by gwoo              #+#    #+#             */
/*   Updated: 2021/05/27 15:50:56 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t					ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int		i;
	unsigned int		src_size;

	i = 0;
	src_size = 0;
	if (!dest || !src)
		return (0);
	while (src[src_size])
		src_size++;
	if (size > 0)
	{
		i = 0;
		while (src[i] && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_size);
}
