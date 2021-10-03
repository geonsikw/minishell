/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:29:19 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/03 12:45:40 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ef_check_set(char c, char *set)
{
	size_t	set_length;
	size_t	i;

	set_length = ft_strlen(set);
	i = 0;
	while (i <= set_length)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	check_same_set(char const *s1, char *set)
{
	int		i;

	i = -1;
	while (s1[++i])
		if (ef_check_set(s1[i], set) == 0)
			return (0);
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	if (check_same_set(s1, (char *)set) == 1)
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1);
	while (ef_check_set(s1[start], (char *)set))
		start++;
	while (ef_check_set(s1[end], (char *)set) && end >= 0)
		end--;
	if (end < start)
		return (ft_strdup(""));
	ptr = (char *)malloc(end - start + 2);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1 + start, end - start + 2);
	return (ptr);
}
