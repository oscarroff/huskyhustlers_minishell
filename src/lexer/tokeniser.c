/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:50:59 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/10 16:40:16 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	tokenise_word(t_parse *p, char *line, t_tree *tree);
static void	tokenise_io_pair(t_token *tok, t_redirect *rdr_flag);

void	tokenise(t_parse *p, t_tree *tree)
{
	size_t	i;

	i = 0;
	if (!p || !tree)
		exit_parser(tree, MSG_UNINTAL);
	while (ft_isspace(p->line[i]))
		i++;
	if (ft_ismetachar(p->line[i]))
		tokenise_redirect(p, p->line + i);
	else
		tokenise_word(p, p->line + i, tree);
	tokenise_io_pair(p->tok, &p->rdr_flag);
	if (p->tok->type == TOK_IO && p->tok->redirect == RDR_HEREDOC)
		heredoc(p->tok, tree);
	p->read_size += i;
}

static void	tokenise_word(t_parse *p, char *line, t_tree *tree)
{
	size_t	i;

	i = 0;
	while (line[i] && ((!ft_ismetachar(line[i]) && !ft_isspace(line[i]))
			|| p->tok->quote_char != '\0'))
	{
		ft_isquote(&p->tok->quote_char, line[i]);
		i++;
	}
	if (i > 0)
	{
		if (!vec_from(p->tok->tok_chars, line, i, sizeof(char)))
			exit_parser(tree, MSG_MALLOCF);
	}
	while (ft_isspace(line[i]))
		i++;
	p->tok->type = TOK_WORD;
	p->tok->quote_char = '\0';
	p->read_size = i;
}

static void	tokenise_io_pair(t_token *tok, t_redirect *rdr_flag)
{
	if (*rdr_flag != RDR_DEFAULT)
	{
		tok->type = TOK_IO;
		tok->redirect = *rdr_flag;
		*rdr_flag = RDR_DEFAULT;
	}
	else if (*rdr_flag == RDR_DEFAULT && tok->type == TOK_REDIRECT)
	{
		*rdr_flag = tok->redirect;
	}
}
