/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:22:49 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/02 23:22:50 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isopchar(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	isquotechar(char c)
{
	return (c == '"' || c == '\'');
}

int	iswordchar(char c)
{
	return (c && !ft_isblank(c) && !isopchar(c));
}
