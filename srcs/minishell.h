/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:12:09 by gwoo              #+#    #+#             */
/*   Updated: 2021/09/16 04:36:43 by gwoo             ###   ########.fr       */
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
void				set_args(char **argv, char *str, int argc);
void				cd_command(t_data *param);
void				pwd_command(int fd);
void				parser(t_data *param);
void				rm_char(char **str, int j);
void				command_or_pipe(t_data *param);
char				*get_env(char **envp, char *env);
char				**copy_env(char **envp, int add);
char				**copy_args(t_data *param);
char				**check_command(char *str, t_data *param);
int					check_builtins(int fd, t_data *param);
int					check_bin(int fd, t_data *param);
int					count_args(char *str);
int					ft_strlen_char(char *str, char c);
void				ft_addchr(char **str, char c);
int					ft_putstrs_fd(char *before, char *str, char *after, int fd);

#endif
