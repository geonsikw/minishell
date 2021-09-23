/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:12:09 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/22 16:33:04 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>

typedef struct s_data{
	int		ac;
	char	**av;
	char	**envp;
	char	**export;
	int		ret;
	char	*str;
	char	*cmds;
	int		child;
}					t_data;

void				free_matrix(char **matrix);
void				set_args(char **av, char *str, int ac);
void				bash_command(t_data *p);
void				cd_command(t_data *p);
void				pwd_command(int fd);
void				exit_command(t_data *p);
void				parser(t_data *p);
void				export_value(t_data *p, int *i);
void				sort_envp(char **envp, int fd, char c);
void				rm_char(char **str, int j);
void				rm_token(char **arg);
void				command_or_pipe(t_data *p);
char				*get_env(char **envp, char *env);
char				**copy_env(char **envp, int add);
char				**export_command(t_data *p, int i);
char				**unset_command(t_data *p, int i);
char				**copy_args(t_data *p);
char				**check_command(char *str, t_data *p);
int					check_builtins(int fd, t_data *p);
int					check_bin(int fd, t_data *p);
int					count_args(char *str);
int					ft_strlen_env(char *str);
int					ft_strlen_char(char *str, char c);
int					check_export_error(char **av, int *i);
void				ft_addchr(char **str, char c);
int					ft_putstrs_fd(char *before, char *str, char *after, int fd);
void				free_matrix(char **matrix);
void				ft_putstrlen_fd(char *s, int len, int fd);
char				*copy_str(char *s);
void				free_p(t_data *p);
void				free_var(char *a, char *b, char *c, char *d);

enum e_token_type
{
	EOL,
	DLESS,
	DGREAT,
	WORD
};

int	isopchar(char c);
int	isquotechar(char c);
int	iswordchar(char c);
#endif
