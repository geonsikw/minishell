/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:22:25 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/03 14:27:07 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_new_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_print_ctrl_c(int sig)
{
	(void)sig;
	write(2, "^C\n", 3);
}

void	sig_nop(int sig)
{
	(void)sig;
}

void	sig_msg_quit(int sig)
{
	write(2, "^\\Quit: ", 8);
	ft_putnbr_fd(sig, 2);
	write(2, "\n", 1);
}
