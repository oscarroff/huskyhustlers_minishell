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
#include <stdint.h>

int	go_back_around(t_parse *p, t_vec *tmp, size_t len, t_tree *tree)
{
	char	*sub_line;
	char	*original;
	t_token	*parent_tok;
	bool	append;
	size_t	tok_count;
	size_t	parent_tok_i;

	ft_printf("\nGBA START\n");
	original = p->line;
	parent_tok = p->tok;
	parent_tok_i = p->tokens->len - 1;
	append = true;
	p->exp_size = 0;
	tok_count = p->tokens->len;
	if (!ft_arena_alloc(tree->a_buf, (void **)&sub_line, tmp->len + 1))
		return (FAIL);
	ft_memcpy(sub_line, tmp->data, tmp->len);
	sub_line[tmp->len] = '\0';
	p->line = sub_line;
	if (ft_isspace(*p->line) || ft_ismetachar(*p->line))
		append = false;
	while (*p->line)
	{
		tok_init(p, tree);
		tokenise(p, tree);
		if (!expandise(p, tree))
			return (SUCCESS);
		unquotise(p->tok, tree);
		p->line += p->read_size;
		if (append == true)
		{
			p->exp_size = p->tok->tok_chars->len;
			parent_tok = *(t_token **)vec_get(p->tokens, parent_tok_i);
			if (!vec_inpend(parent_tok->tok_chars, p->tok->tok_chars, len)
				|| !vec_remove(p->tokens, p->tokens->len - 1))
				exit_parser(tree, MSG_MALLOCF);
			append = false;
		}
		// TODO: Append works but PREPENDING needs to be fixed!
	}
	while (p->tokens->len > tok_count)
	{
		if (!vec_remove(p->tokens, p->tokens->len - 1))
			exit_parser(tree, MSG_MALLOCF);
	}
	p->line = original;
	p->tok = *(t_token **)vec_get(p->tokens, parent_tok_i);
	// printf("rd_size: %zu exp_size: %zu\n", p->read_size, p->exp_size);
	ft_printf("GBA END len: %i\n\n", (uint8_t)p->tok->tok_chars->len);
	return (SUCCESS);
}
