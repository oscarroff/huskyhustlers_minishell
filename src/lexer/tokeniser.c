/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:50:59 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 20:24:32 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	tokenise_quote(t_token *tok, char *line, t_tree *tree);
static void	tokenise_word(t_token *tok, char *line, t_tree *tree);
static void	tokenise_io_pair(t_token *tok, t_redirect *rdr_flag);

void	tokenise(t_token *tok, t_redirect *rdr_flag, char *line, t_tree *tree)
{
	size_t	i;

	i = 0;
	if (!tok || !line || !tree)
		exit_parser(tree, MSG_UNINTAL);
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '"' || line[i] == '\'')
		tokenise_quote(tok, line + i, tree);
	else if (ft_ismetachar(line[i]))
		tokenise_redirect(tok, line + i);
	else
		tokenise_word(tok, line + i, tree);
	tokenise_io_pair(tok, rdr_flag);
	if (tok->type == TOK_IO && tok->redirect == RDR_HEREDOC)
		heredoc(tok, tree);
	tok->read_size += i;
}

static void	tokenise_quote(t_token *tok, char *line, t_tree *tree)
{
	size_t	i;

	tok->quote_char = *line;
	i = 0;
	while (line[i + 1] != tok->quote_char)
	{
		if (line[i] == '$' && tok->quote_char == '"' && tok->expand == false)
			tok->expand = true;
		i++;
	}
	if (i > 0)
		if (!vec_from(tok->tok_chars, line + 1, i, sizeof(char)))
			exit_parser(tree, MSG_MALLOCF);
	tok->type = TOK_QUOTATION;
	if (tok->quote_char == '\'')
		tok->quote_type = QUO_SINGLE;
	if (tok->quote_char == '"')
		tok->quote_type = QUO_DOUBLE;
	tok->read_size = i + 2;
}

static void	tokenise_word(t_token *tok, char *line, t_tree *tree)
{
	size_t	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]) && !ft_ismetachar(line[i]))
	{
		if (line[i] == '$' && tok->expand == false)
			tok->expand = true;
		i++;
	}
	if (i > 0)
	{
		if (!vec_from(tok->tok_chars, line, i, sizeof(char)))
			exit_parser(tree, MSG_MALLOCF);
	}
	while (ft_isspace(line[i]))
		i++;
	tok->type = TOK_WORD;
	tok->read_size = i;
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
		*rdr_flag = tok->redirect;
}
