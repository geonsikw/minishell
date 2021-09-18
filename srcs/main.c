/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 14:27:12 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/17 21:14:53 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include "minishell.h"

/*
void	put_prompt(void)
{
	char	cwd[4097];

	getcwd(cwd, 4096);
	ft_putstr_fd(cwd, 2);
	write(2, " ", 1);
}

void	sig_handler(int sig)
{
	char	cwd[4097];

	if (sig == SIGINT)
	{
		getcwd(cwd, 4096);
		write(2, "\n", 1);
		ft_putstr_fd(cwd, 2);
		write(2, " ", 1);
	}
}

void	init_p(t_data **p, char **av, char **envp, int *str)
{
	(*p) = (t_data *)malloc(sizeof(t_data));
	(*p)->envp = copy_env(envp, 0);
	(*p)->export = (char **)ft_calloc(sizeof(char *), 1);
	(*p)->av = av;
	(*p)->ret = 0;
	(*p)->str = 0;
	(*p)->child = 0;
	str[0] = 1;
}

int	main(int ac, char **av, char **envp)
{
	t_data	*p;
	int		str[2];
	char	c;

	if (ac != 1)
		return (1);
	init_p(&p, av, envp, str);
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	while (1)
	{
		if (str[0])
			put_prompt();
		while ((str[0] = read(1, &c, 1)) && c != '\n')
			ft_addchr(&(p->str), c);
		str[1] = (int)ft_strlen(p->str);
		if (c == '\n')
			parser(p);
	}
	return (0);
}
*/

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_p(t_data *p, char **av, char **envp)
{
	p->envp = copy_env(envp, 0);
	p->export = (char **)ft_calloc(sizeof(char *), 1);
	p->av = av;
	p->ret = 0;
	p->str = 0;
	p->child = 0;
}

int	initial_settings(void)
{
	struct termios	t;

	rl_catch_signals = 0;
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return (-1);
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		return (-1);
	if (isatty(0) && tcgetattr(0, &t) < 0)
		return (-1);
	t.c_lflag &= ~ECHOCTL;
	if (isatty(0) && tcsetattr(0, TCSANOW, &t) < 0)
		return (-1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	p;

	if (ac != 1 || initial_settings() < 0)
		return (1);
	init_p(&p, av, envp);
	while (1)
	{
		p.str = readline("prompt$ ");
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
