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

#include "parsing.h"

static void	redirect_set(t_parse *p, t_redirect rdr, size_t rd_size);

void	tokenise_redirect(t_parse *p, char *line)
{
	if (*line == '|')
	{
		p->tok->type = TOK_PIPE;
		p->tok->redirect = RDR_DEFAULT;
		p->read_size = 1;
	}
	else if (line[0] == '<' && line[1] != '<')
		redirect_set(p, RDR_READ, 1);
	else if (line[0] == '>' && line[1] != '>')
		redirect_set(p, RDR_WRITE, 1);
	else if (line[0] == '<' && line[1] == '<')
		redirect_set(p, RDR_HEREDOC, 2);
	else if (line[0] == '>' && line[1] == '>')
		redirect_set(p, RDR_APPEND, 2);
}

static void	redirect_set(t_parse *p, t_redirect rdr, size_t rd_size)
{
	p->tok->type = TOK_REDIRECT;
	p->tok->redirect = rdr;
	p->read_size = rd_size;
}
