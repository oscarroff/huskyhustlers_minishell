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

static void	tokenise_quote(t_token *tok, char *line, t_tree *tree);
static void	tokenise_redirect(t_token *tok, char *line);
static void	rdr_set(t_token *tok, e_redirect rdr, size_t rd_size);
static void	tokenise_word(t_token *tok, char *line, t_tree *tree);

void	tokenise(t_token *tok, char *line, t_tree *tree)
{
	if (!tok || !line || !tree)
		clean_exit(tree, MSG_UNINTAL);
	if (*line == '"' || *line == '\'')
		tokenise_quote(tok, line, tree);
	else if (ft_ismetachar(*line))
		tokenise_redirect(tok, line);
	else
		tokenise_word(tok, line, tree);
}

static void	tokenise_quote(t_token *tok, char *line, t_tree *tree)
{
	size_t	i;

	tok->quote = *line;
	i = 0;
	while (line[i + 1] != tok->quote)
	{
		if (line[i] == '$' && tok->quote == '"' && tok->expand == false)
			tok->expand = true;
		i++;
	}
	if (i > 0)
		if (!vec_from(tok->tok_chars, line + 1, i, sizeof(char)))
			clean_exit(tree, "malloc fail 2");
	tok->type = TOK_QUOTATION;
	tok->read_size = i + 2;
}

static void	tokenise_redirect(t_token *tok, char *line)
{
	if (*line == '|')
		rdr_set(tok, RDR_PIPE, 1);
	else if (line[0] == '<' && line[1] != '<')
		rdr_set(tok, RDR_FILE, 1);
	else if (line[0] == '>' && line[1] != '>')
		rdr_set(tok, RDR_WRITE, 1);
	else if (line[0] == '<' && line[1] == '<')
		rdr_set(tok, RDR_FILE_DELIM, 2);
	else if (line[0] == '>' && line[1] == '>')
		rdr_set(tok, RDR_APPEND, 2);
}

static void	rdr_set(t_token *tok, e_redirect rdr, size_t rd_size)
{
	tok->type = TOK_REDIRECT;
	tok->redirect = rdr;
	tok->read_size = rd_size;
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
	if (!tok->tok_chars)
		ft_printf("I got here\n");
	if (i > 0)
	{
		ft_printf("%s\n", line);
		if (!vec_from(tok->tok_chars, line, i, sizeof(char)))
			clean_exit(tree, MSG_MALLOCF);
	}
	tok->type = TOK_WORD;
	tok->read_size = i;
	vec_printf(tok->tok_chars, 's');
}
