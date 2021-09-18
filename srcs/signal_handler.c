#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

void	prompt_on_newline(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	print_nl(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	nop(int sig)
{
	(void)sig;
}
