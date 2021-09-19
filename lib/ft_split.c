/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 22:14:12 by gwoo              #+#    #+#             */
/*   Updated: 2021/05/28 21:32:31 by gwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**letfree(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int		ft_word_count(char const *str, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			cnt++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (cnt);
}

char	*ft_copy_word(char *word, char const *str, int j, int word_len)
{
	int		i;

	i = 0;
	while (word_len > 0)
		word[i++] = str[j - word_len--];
	word[i] = '\0';
	return (word);
}

char	**ft_str_to_tab(char **tab, char const *str, char c, int word)
{
	int		i;
	int		j;
	int		word_len;

	i = 0;
	j = 0;
	word_len = 0;
	while (str[j] && i < word)
	{
		while (str[j] && str[j] == c)
			j++;
		while (str[j] && str[j] != c)
		{
			j++;
			word_len++;
		}
		if (!(tab[i] = (char *)malloc(sizeof(char) * (word_len + 1))))
			return (letfree(tab));
		ft_copy_word(tab[i], str, j, word_len);
		word_len = 0;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	**ft_split(char const *str, char c)
{
	int		word;
	char	**tab;

	if (str == 0)
		return (NULL);
	word = ft_word_count(str, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (word + 1))))
		return (NULL);
	ft_str_to_tab(tab, str, c, word);
	return (tab);
}
