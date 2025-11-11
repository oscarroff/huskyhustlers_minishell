/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:50:59 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/10 11:56:24 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static void	tokenise_quote(t_token *token, char *line, t_tree *tree);
static void	tokenise_redirect(t_token *token, char *line);
static void	rdr_set(t_token *tok, e_redirect rdr, size_t rd_size);
static void	tokenise_word(t_token *token, char *line, t_tree *tree);

void	tokenise(t_token *token, char *line, t_tree *tree)
{
	if (!token || !line || !tree)
		clean_exit(tree, MSG_UNINTAL);
	if (*line == '"' || *line == '\'')
		tokenise_quote(token, line, tree);
	else if (ft_ismetachar(*line))
		tokenise_redirect(token, line);
	else
		tokenise_word(token, line, tree);
}

static void	tokenise_quote(t_token *token, char *line, t_tree *tree)
{
	size_t	i;

	token->quote = *line;
	i = 0;
	while (line[i + 1] != token->quote)
	{
		if (line[i] == '$' && token->quote == '"' && token->expand == false)
			token->expand = true;
		i++;
	}
	if (i > 0)
		if (!vec_from(token->tok_chars, line + 1, i, sizeof(char)))
			clean_exit(tree, "malloc fail 2");
	token->type = TOK_QUOTATION;
	token->read_size = i + 2;
}

static void	tokenise_redirect(t_token *token, char *line)
{
	if (*line == '|')
		rdr_set(token, RDR_PIPE, 1);
	else if (line[0] == '<' && line[1] != '<')
		rdr_set(token, RDR_FILE, 1);
	else if (line[0] == '>' && line[1] != '>')
		rdr_set(token, RDR_WRITE, 1);
	else if (line[0] == '<' && line[1] == '<')
		rdr_set(token, RDR_FILE_DELIM, 2);
	else if (line[0] == '>' && line[1] == '>')
		rdr_set(token, RDR_APPEND, 2);
}

static void	rdr_set(t_token *tok, e_redirect rdr, size_t rd_size)
{
	tok->type = TOK_REDIRECT;
	tok->redirect = rdr;
	tok->read_size = rd_size;
}

static void	tokenise_word(t_token *token, char *line, t_tree *tree)
{
	size_t	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]) && !ft_ismetachar(line[i]))
	{
		if (line[i] == '$' && token->expand == false)
			token->expand = true;
		i++;
	}
	if (i > 0)
	{
		if (!vec_from(token->tok_chars, line, i, sizeof(char)))
			clean_exit(tree, "malloc fail 2");
	}
	token->type = TOK_WORD;
	token->read_size = i;
}
