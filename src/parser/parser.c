/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:41:21 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 17:00:21 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static void	init_lexer(t_vec **tokens, t_tree *tree);
static void	init_tok(t_token **tok, t_vec *tokens, t_tree *tree);
static bool	ft_nothingtodo(char **line);

int	parser(t_tree *tree, char *line, t_flag mode_flag)
{
	t_vec		*tokens;
	t_token		*tok;
	t_redirect	rdr_flag;

	if (!tree || !line || !valid_input(line))
		return (FAIL);
	if (ft_nothingtodo(&line))
		return (SUCCESS);
	tokens = NULL;
	tok = NULL;
	rdr_flag = RDR_DEFAULT;
	init_lexer(&tokens, tree);
	while (*line)
	{
		init_tok(&tok, tokens, tree);
		tokenise(tok, &rdr_flag, line, tree);
		if (tok->expand == true)
			expandise(tok, tree);
		line += tok->read_size;
	}
	commandise(tree, tokens);
	if (mode_flag == FLAG_DEBUG)
		print_debugging(tokens, tree);
	return (SUCCESS);
}

static void	init_tok(t_token **tok, t_vec *tokens, t_tree *tree)
{
	t_token	*new;

	new = NULL;
	if (!ft_arena_alloc(tree->arena, (void **)&new, sizeof(t_token)))
		clean_exit(tree, MSG_MALLOCF);
	new->tok_chars = NULL;
	if (!vec_alloc(&new->tok_chars, tree->arena))
		clean_exit(tree, MSG_MALLOCF);
	new->type = TOK_DEFAULT;
	new->redirect = RDR_DEFAULT;
	new->quote_type = QUO_DEFAULT;
	new->quote_char = '\0';
	new->expand = false;
	new->read_size = 1;
	*tok = new;
	if (!vec_push(tokens, tok))
		clean_exit(tree, MSG_MALLOCF);
}

static bool	ft_nothingtodo(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (!**line)
		return (true);
	return (false);
}

static void	init_lexer(t_vec **tokens, t_tree *tree)
{
	if (!tokens || !tree)
		clean_exit(tree, MSG_UNINTAL);
	if (!ft_arena_init(&tree->arena, ARENA_BUF))
		clean_exit(tree, MSG_MALLOCF);
	if (!vec_alloc(tokens, tree->arena))
		clean_exit(tree, MSG_MALLOCF);
	if (!vec_new(*tokens, 0, sizeof(t_token *)))
		clean_exit(tree, MSG_MALLOCF);
}
