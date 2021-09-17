/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:19:51 by gwoo              #+#    #+#             */
/*   Updated: 2021/05/27 15:51:26 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t j;

	if (*to_find == 0)
		return ((char*)(str));
	if (len == 0)
		return (NULL);
	i = 0;
	while (str[i] && i < len && len > 0)
	{
		j = 0;
		while (to_find[j] && (to_find[j] == str[i + j] && i + j < len))
			j++;
		if (to_find[j] == 0)
			return (&((char*)str)[i]);
		i++;
	}
	return (NULL);
}
