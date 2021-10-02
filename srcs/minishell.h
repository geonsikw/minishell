/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwoo <gwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:12:09 by gwoo              #+#    #+#             */
/*   Updated: 2021/10/02 23:07:59 by jihkwon          ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

/*
void				free_matrix(char **matrix);
void				set_args(char **av, char *str, int ac);
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
char				**update_envp(t_data *p, int j);
char				**unset_command(t_data *p, int i);
char				**copy_args(t_data *p);
char				**check_command(char *str, t_data *p);
int					check_builtins(int fd, t_data *p);
int					check_bin(int fdin, int fdout, t_data *p);
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
void				skip_spaces(char **str);
void				excutable(t_data *param);
int					gnl(int fd, char **line);
void				child_sig_handler(int sig);

void	prompt_on_newline(int sig);
void	print_nl(int sig);
void	nop(int sig);

int	isopchar(char c);
int	isquotechar(char c);
int	iswordchar(char c);
int	get_token(char **token, int *type, char **line);
void	errmsg_syntax(char *token);
void	expand_args(t_data *p);
char	*expand_redir_filename(char *word, char *envp[], int exitcode);
char	*remove_quotes(char *word);
int	set_fd_in(t_data *p);
int	set_fd_out(t_data *p);
char	*strjoin_replace(char *s1, char *s2);
char	*ft_strtok(char **str, char *delim);
*/

typedef struct s_data{
	int		ac;
	char	**av;
	char	**envp;
	char	**export;
	int		ret;
	char	*str;
	char	*cmds;
	int		child;
}	t_data;

enum e_token_type
{
	EOL,
	DLESS,
	DGREAT,
	WORD
};

enum e_parse_error
{
	ETOKEN = 1,
	ESYNTAX
};

/* wasq: was quoted */
struct s_field
{
	int		wasq;
	char	*str;
};

/* args.c */

/* bin.c */
int				check_bin(int fdin, int fdout, t_data *p);

/* builtins.c */

/* cd.c */
void			cd_command(t_data *p);

/* command.c */
char			**check_command(char *str, t_data *p);

/* echo.c */
void			echo_command(t_data *p, int fd);

/* env.c */
void			env_command(t_data *p, int fd);

/* environment.c */
char			**update_envp(t_data *p, int j);
char			*get_env(char **envp, char *env);
char			**copy_env(char **envp, int add);

/* error_message.c */
void			errmsg_syntax(char *token);

/* excutable.c */

/* exit.c */
void			exit_command(t_data *p);

/* export1.c */
char			**export_command(t_data *p, int fd);

/* export2.c */
void			export_value(t_data *p, int *i);
int				check_export_error(char **av, int *i);
void			sort_envp(char **envp, int fd, char c);

/* field.c */
struct s_field	*new_field(int wasq, char *str);
struct s_field	*merge_field(struct s_field *f1, struct s_field *f2);
void			free_field(void *f);

/* get_token.c */
int				get_token(char **token, int *type, char **line);

/* gnl.c */

/* here_document.c */
char			*read_heredoc(char *delim_token);

/* len.c */
void			ft_putstrlen_fd(char *s, int len, int fd);
int				ft_strlen_char(char *str, char c);

/* parser1.c */
void			parser(t_data *p);

/* parser2.c */
int				parse_line(t_list **token_list, char **token, int *type,
					char **line);

/* pipe.c */
void			command_or_pipe(t_data *p);

/* redirection.c */
int				set_fd_in(t_data *p);
int				set_fd_out(t_data *p);

/* remove.c */
void			free_p(t_data *p);
void			free_matrix(char **matrix);

/* signal_handler.c */
void			sig_new_prompt(int sig);
void			sig_print_nl(int sig);
void			sig_nop(int sig);

/* unset.c */
char			**unset_command(t_data *p, int j);

/* utils1.c */
int				isopchar(char c);
int				isquotechar(char c);
int				iswordchar(char c);

/* utils2.c */
int				ft_putstrs_fd(char *before, char *str, char *after, int fd);
int				digits_only(char *str);
char			*getname(char **word);
char			*strjoin_replace(char *s1, char *s2);
char			*ft_strtok(char **str, char *delim);

/* word_expansion1.c */
char			*expand_redir_filename(char *word, char *envp[], int exitcode);
char			*remove_quotes(char *word);
void			expand_args(t_data *p);

/* word_expansion2.c */
t_list			*expand_word(char *word, char *envp[], int exitcode);

/* word_expansion3.c */
char			*expand_param(char **word, char *envp[], int exitcode);
char			*expand_quote(char **word, char *envp[], int exitcode);
t_list			*split_to_list(char *str);
#endif
