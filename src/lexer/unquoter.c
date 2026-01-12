/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:54:06 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/10 12:44:46 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	unquotise(t_token *tok, t_tree *tree)
{
	char	*src;
	size_t	i;

	src = (char *)tok->tok_chars->data;
	i = tok->tok_chars->len;
	while (i-- > 0)
	{
		if (ft_isquote(&tok->quote_char, src[i]))
			if (!vec_remove(tok->tok_chars, i))
				exit_parser(tree, MSG_MALLOCF);
	}
}
