/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:04:20 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 16:58:16 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static void	rdr_set(t_token *tok, t_redirect rdr, size_t rd_size);

void	handle_redirect(t_token *tok, char *line)
{
	if (*line == '|')
		tok->type = TOK_PIPE;
	else if (line[0] == '<' && line[1] != '<')
		rdr_set(tok, RDR_READ, 1);
	else if (line[0] == '>' && line[1] != '>')
		rdr_set(tok, RDR_WRITE, 1);
	else if (line[0] == '<' && line[1] == '<')
		rdr_set(tok, RDR_HEREDOC, 2);
	else if (line[0] == '>' && line[1] == '>')
		rdr_set(tok, RDR_APPEND, 2);
}

static void	rdr_set(t_token *tok, t_redirect rdr, size_t rd_size)
{
	tok->type = TOK_REDIRECT;
	tok->redirect = rdr;
	tok->read_size = rd_size;
}
