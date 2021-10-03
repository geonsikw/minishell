/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 14:27:12 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/03 14:27:51 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "minishell.h"

void	init_p(t_data *p, char **av, char **envp)
{
	p->envp = copy_env(envp, 0);
	p->export = (char **)ft_calloc(sizeof(char *), 1);
	p->av = av;
	p->ret = 0;
	p->str = 0;
	p->child = 0;
}

void	config_terminal(void)
{
	struct termios	t;

	rl_catch_signals = 0;
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

int	main(int ac, char **av, char **envp)
{
	t_data	p;

	if (ac != 1)
		return (1);
	config_terminal();
	init_p(&p, av, envp);
	while (1)
	{
		signal(SIGINT, sig_new_prompt);
		signal(SIGQUIT, sig_nop);
		p.str = readline("prompt$ ");
		signal(SIGINT, sig_print_ctrl_c);
		signal(SIGQUIT, sig_msg_quit);
		if (!p.str)
		{
			free(p.export);
			free_matrix(p.envp);
			ft_putendl_fd("exit", 1);
			return (0);
		}
		if (p.str[0])
			add_history(p.str);
		parser(&p);
		free(p.str);
	}
}
