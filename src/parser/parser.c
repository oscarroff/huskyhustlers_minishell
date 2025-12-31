/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:41:21 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/27 14:20:22 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	lexer_init(t_vec **tokens, t_tree *tree);
static void	tok_init(t_token **tok, t_vec *tokens, t_tree *tree);
static bool	ft_nothingtodo(char *line);
static bool	ft_reallynothingtodo(t_vec *tokens);

int	parser(t_tree *tree, char *line)
{
	t_vec		*tokens;
	t_token		*tok;
	t_redirect	rdr_flag;

	if (ft_nothingtodo(line))
		return (SUCCESS);
	if (!tree || !valid_input(line))
		return (FAIL);
	tokens = NULL;
	tok = NULL;
	rdr_flag = RDR_DEFAULT;
	lexer_init(&tokens, tree);
	while (*line)
	{
		tok_init(&tok, tokens, tree);
		tokenise(tok, &rdr_flag, line, tree);
		if (tok->expand == true)
			expandise(tok, tree);
		line += tok->read_size;
	}
	if (ft_reallynothingtodo(tokens))
		return (SUCCESS);
	commandise(tree, tokens);
	if (tree->mode == FLAG_DEBUG || tree->mode == FLAG_DEBUG_ENVP)
		print_debugging(tokens, tree);
	return (SUCCESS);
}

static void	lexer_init(t_vec **tokens, t_tree *tree)
{
	if (!tokens || !tree)
		exit_parser(tree, MSG_UNINTAL);
	if (!ft_arena_init(&tree->a_buf, ARENA_BUF))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_alloc(tokens, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_new(*tokens, 0, sizeof(t_token *)))
		exit_parser(tree, MSG_MALLOCF);
}

static void	tok_init(t_token **tok, t_vec *tokens, t_tree *tree)
{
	t_token	*new;

	new = NULL;
	if (!ft_arena_alloc(tree->a_buf, (void **)&new, sizeof(t_token)))
		exit_parser(tree, MSG_MALLOCF);
	new->tok_chars = NULL;
	if (!vec_alloc(&new->tok_chars, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	new->type = TOK_DEFAULT;
	new->redirect = RDR_DEFAULT;
	new->quote_type = QUO_DEFAULT;
	new->quote_char = '\0';
	new->expand = false;
	new->read_size = 1;
	*tok = new;
	if (!vec_push(tokens, tok))
		exit_parser(tree, MSG_MALLOCF);
}

static bool	ft_nothingtodo(char *line)
{
	if (line && ft_strlen(line) == 0)
		return (true);
	while (ft_isspace(*line))
		line++;
	if (!*line)
		return (true);
	return (false);
}

static bool	ft_reallynothingtodo(t_vec *tokens)
{
	t_token	*tok;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (i < tokens->len)
	{
		tok = *(t_token **)vec_get(tokens, i);
		len += tok->tok_chars->len;
		if (len > 0)
			return (false);
		i++;
	}
	return (true);
}
