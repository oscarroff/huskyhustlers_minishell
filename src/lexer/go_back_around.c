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

int	go_back_around(t_parse *p, t_vec *tmp, size_t len, t_tree *tree)
{
	char	*sub_line;
	char	*original;
	t_token	*parent_tok;
	bool	append;
	// size_t	i;

	original = p->line;
	parent_tok = p->tok;
	append = true;
	if (!ft_arena_alloc(tree->a_buf, (void **)&sub_line, tmp->len + 1))
		return (FAIL);
	ft_memcpy(sub_line, tmp->data, tmp->len);
	sub_line[tmp->len] = '\0';
	p->line = sub_line;
	if (ft_isspace(*p->line) || ft_ismetachar(*p->line))
		append = false;
	// i = 0;
	while (*p->line)
	{
		tok_init(p, tree);
		tokenise(p, tree);
		if (!expandise(p, tree))
			return (SUCCESS);
		unquotise(p->tok, tree);
		p->line += p->read_size;
		// i += p->read_size;
		if (append == true)
		{
			if (!vec_inpend(parent_tok->tok_chars, p->tok->tok_chars, len)
				|| !vec_remove(p->tokens, p->tokens->len - 1))
				exit_parser(tree, MSG_MALLOCF);
			append = false;
		}
	}
	p->line = original;
	return (SUCCESS);
}
