/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:41:21 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/15 17:05:16 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "debugging.h" //FIXME: Remove for release

static void	lexer_init(t_parse *p, char *line, t_tree *tree);
static bool	ft_nothingtodo(char *line);
static bool	ft_reallynothingtodo(t_vec *tokens);

int	parser(t_tree *tree, char *line)
{
	t_parse		p;

	if (ft_nothingtodo(line) || !tree || !valid_input(line, tree))
		return (SUCCESS);
	lexer_init(&p, line, tree);
	while (*p.line)
	{
		tok_init(&p, tree);
		tokenise(&p, tree);
		if (!expandise(&p, tree))
			return (SUCCESS);
		unquotise(p.tok, tree);
		p.line += p.read_size;
	}
	if (ft_reallynothingtodo(p.tokens) || !super_valid_input(tree, p.tokens)
		|| !commandise(tree, p.tokens))
		return (SUCCESS);
	if (tree->mode == FLAG_DEBUG || tree->mode == FLAG_DEBUG_ENVP)
		print_debugging(p.tokens, tree);
	return (SUCCESS);
}

static void	lexer_init(t_parse *p, char *line, t_tree *tree)
{
	t_vec	*tokens;

	ft_memset(p, 0, sizeof(t_parse));
	p->tokens = NULL;
	p->tok = NULL;
	if (!tree)
		exit_parser(tree, MSG_UNINTAL);
	if (!ft_arena_init(&tree->a_buf, ARENA_BUF))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_alloc(&tokens, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_new(tokens, 0, sizeof(t_token *)))
		exit_parser(tree, MSG_MALLOCF);
	p->tokens = tokens;
	p->rdr_flag = RDR_DEFAULT;
	p->line = line;
	p->read_size = 1;
}

void	tok_init(t_parse *p, t_tree *tree)
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
	p->tok = new;
	if (!vec_push(p->tokens, &p->tok))
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
