/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:20:30 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/02 23:20:34 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* redirection	: '<'		WORD
 * 				| '>'		WORD
 * 				| DLESS		WORD
 * 				| DGREAT	WORD
 */

int	parse_redirection(t_list **token_list, char **token, int *type, char **line)
{
	int	heredoc;

	if (*type != '<' && *type != '>' && *type != DLESS && *type != DGREAT)
		return (-ESYNTAX);
	heredoc = *type == DLESS;
	ft_lstadd_front(token_list, ft_lstnew(*token));
	if (get_token(token, type, line) < 0)
		return (-ETOKEN);
	if (*type != WORD)
		return (-ESYNTAX);
	if (heredoc)
	{
		ft_lstadd_front(token_list, ft_lstnew(read_heredoc(*token)));
		free(*token);
	}
	else
		ft_lstadd_front(token_list, ft_lstnew(*token));
	if (get_token(token, type, line) < 0)
		return (-ETOKEN);
	return (0);
}

/* command_element	: WORD
 * 					| redirection
 */

int	parse_command_element(
		t_list **token_list, char **token, int *type, char **line)
{
	if (*type != WORD)
		return (parse_redirection(token_list, token, type, line));
	ft_lstadd_front(token_list, ft_lstnew(*token));
	if (get_token(token, type, line) < 0)
		return (-ETOKEN);
	return (0);
}

/* command	: command_element
 * 			| command_element	command
 */

int	parse_command(t_list **token_list, char **token, int *type, char **line)
{
	int	err;

	err = parse_command_element(token_list, token, type, line);
	if (err)
		return (err);
	if (*type == '|' || *type == EOL)
		return (0);
	return (parse_command(token_list, token, type, line));
}

/* pipeline	: command
 * 			| command	'|'	pipeline
 */

int	parse_pipeline(t_list **token_list, char **token, int *type, char **line)
{
	int	err;

	err = parse_command(token_list, token, type, line);
	if (err)
		return (err);
	if (*type != '|')
		return (0);
	ft_lstadd_front(token_list, ft_lstnew(*token));
	if (get_token(token, type, line) < 0)
		return (-ETOKEN);
	return (parse_pipeline(token_list, token, type, line));
}

/* line	: empty
 * 		| pipeline
 */

int	parse_line(t_list **token_list, char **token, int *type, char **line)
{
	char	*token_saved;
	int		err;

	token_saved = *token;
	err = parse_pipeline(token_list, token, type, line);
	if (!err)
		return (0);
	if (err == -ESYNTAX && *token == token_saved)
		return (0);
	return (err);
}
