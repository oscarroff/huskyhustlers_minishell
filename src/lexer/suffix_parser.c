/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suffix_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:01:59 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/15 15:05:45 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	suffix_parse(t_vec **dst, t_token *parent_tok,
						size_t insert_at, t_tree *tree)
{
	size_t	suffix_len;
	t_vec	*suffix;
	char	*tmp;

	tmp = NULL;
	suffix = NULL;
	*dst = NULL;
	if (insert_at >= parent_tok->tok_chars->len)
		return ;
	suffix_len = parent_tok->tok_chars->len - insert_at;
	if (suffix_len > 0)
	{
		tmp = vec_get(parent_tok->tok_chars, insert_at);
		if (!vec_alloc(&suffix, tree->a_buf)
			|| !vec_from(suffix, tmp, suffix_len, sizeof(char)))
			exit_parser(tree, MSG_MALLOCF);
		if (!vec_trim(parent_tok->tok_chars, insert_at, suffix_len))
			exit_parser(tree, MSG_MALLOCF);
	}
	*dst = suffix;
}

int	suffix_insert(t_vec *suffix, t_token *last_tok,
						t_parse *p, t_tree *tree)
{
	t_parse	sub;

	if (!vec_inpend(last_tok->tok_chars, suffix, last_tok->tok_chars->len))
		exit_parser(tree, MSG_MALLOCF);
	if (ft_memchr(suffix->data, '$', suffix->len))
	{
		ft_memset(&sub, 0, sizeof(t_parse));
		sub.tok = last_tok;
		sub.tokens = p->tokens;
		if (!expandise(&sub, tree))
			return (FAIL);
	}
	return (SUCCESS);
}
