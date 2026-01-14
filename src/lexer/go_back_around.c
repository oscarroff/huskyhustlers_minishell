/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_back_around.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:52:25 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/12 15:24:57 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	tok_index(size_t *i, t_vec *tokens, t_token *tok, t_tree *tree);
static int	gba_init(t_parse *sub, t_vec *tmp, t_tree *tree);
static int	gba_parse(t_parse *sub, t_vec *tmp, t_tree *tree);
static void	gba_insert(t_parse *p, t_parse sub, size_t parent_i, t_tree *tree);

static void	tok_index(size_t *i, t_vec *tokens, t_token *tok, t_tree *tree)
{
	size_t	j;

	j = 0;
	while (j < tokens->len)
	{
		if (*(t_token **)vec_get(tokens, j) == tok)
		{
			*i = j;
			return ;
		}
		j++;
	}
	exit_parser(tree, MSG_UNINTAL);
}

static int	gba_init(t_parse *sub, t_vec *tmp, t_tree *tree)
{
	t_vec	*sub_tokens;
	char	*sub_line;

	if (!ft_arena_alloc(tree->a_buf, (void **)&sub_line, tmp->len + 1))
		return (FAIL);
	ft_memcpy(sub_line, tmp->data, tmp->len);
	sub_line[tmp->len] = '\0';
	ft_memset(sub, 0, sizeof(t_parse));
	sub->line = sub_line;
	sub->read_size = 1;
	sub->rdr_flag = RDR_DEFAULT;
	sub->tokens = NULL;
	sub->tok = NULL;
	if (!vec_alloc(&sub_tokens, tree->a_buf)
		|| !vec_new(sub_tokens, 0, sizeof(t_token *)))
		exit_parser(tree, MSG_MALLOCF);
	sub->tokens = sub_tokens;
	return (SUCCESS);
}

static int	gba_parse(t_parse *sub, t_vec *tmp, t_tree *tree)
{
	if (!gba_init(sub, tmp, tree))
		return (FAIL);
	while (*sub->line)
	{
		tok_init(sub, tree);
		tokenise(sub, tree);
		if (!expandise(sub, tree))
			return (FAIL);
		unquotise(sub->tok, tree);
		sub->line += sub->read_size;
	}
	return (SUCCESS);
}

static void	gba_insert(t_parse *p, t_parse sub, size_t parent_i, t_tree *tree)
{
	t_token	*child;
	size_t	k;

	k = 1;
	while (k < sub.tokens->len)
	{
		child = *(t_token **)vec_get(sub.tokens, k);
		if (!vec_insert(p->tokens, &child, parent_i + k))
			exit_parser(tree, MSG_MALLOCF);
		k++;
	}
}

int	go_back_around(t_parse *p, t_vec *tmp, size_t insert_at, t_tree *tree)
{
	t_parse	sub;
	t_token	*parent_tok;
	size_t	parent_i;

	parent_tok = p->tok;
	if (!gba_parse(&sub, tmp, tree))
		return (FAIL);
	if (sub.tokens->len == 0)
		return (SUCCESS);
	if (!vec_inpend(parent_tok->tok_chars,
			(*(t_token **)vec_get(sub.tokens, 0))->tok_chars, insert_at))
		exit_parser(tree, MSG_MALLOCF);
	tok_index(&parent_i, p->tokens, parent_tok, tree);
	gba_insert(p, sub, parent_i, tree);
	return (SUCCESS);
}
