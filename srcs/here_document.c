/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihkwon <jihkwon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:19:27 by jihkwon           #+#    #+#             */
/*   Updated: 2021/10/02 23:19:43 by jihkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_heredoc(char *delim_token)
{
	char	*heredoc;
	char	*delim;
	char	*line;

	signal(SIGINT, sig_nop);
	heredoc = ft_strdup("");
	delim = remove_quotes(delim_token);
	while (1)
	{
		line = readline("> ");
		if (!line)
			ft_putstrs_fd("minishell: warning: here-document delimited "
				"by end-of-file (wanted `", delim, "')\n", 2);
		if (!line || ft_strcmp(line, delim) == 0)
			break ;
		heredoc = strjoin_replace(heredoc, ft_strjoin(line, "\n"));
		free(line);
	}
	free(line);
	free(delim);
	signal(SIGINT, sig_print_nl);
	return (heredoc);
}
