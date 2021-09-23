/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:12:29 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/22 17:06:19 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_str;
	unsigned char	*s2_str;

//	if (!s1 || !s2)
//		return (0);
	s1_str = (unsigned char *)s1;
	s2_str = (unsigned char *)s2;
	while (0 < n--)
		if (*(s1_str++) != *(s2_str++))
			return (*(--s1_str) - *(--s2_str));
	return (0);
}
