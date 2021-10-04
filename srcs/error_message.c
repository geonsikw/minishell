/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:16:00 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/04 12:17:13 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errmsg_syntax(char *token)
{
	if (ft_strcmp(token, "") == 0)
		token = "newline";
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}

void	perror2(char *s1, char *s2)
{
	if (s1 && s1[0])
	{
		ft_putstr_fd(s1, 2);
		write(2, ": ", 2);
	}
	perror(s2);
}
