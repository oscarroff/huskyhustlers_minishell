/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:54:06 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/15 14:22:00 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	unquotise(t_token *tok, t_tree *tree)
{
	char	*src;
	size_t	i;

	src = (char *)tok->tok_chars->data;
	i = 0;
	while (i < tok->tok_chars->len)
	{
		if (ft_isquote(&tok->quote_char, src[i]))
		{
			if (!vec_remove(tok->tok_chars, i))
				exit_parser(tree, MSG_MALLOCF);
		}
		else if (src[i] == '$' && tok->quote_char == '\0'
			&& src[i + 1] && src[i + 1] == '\'')
		{
			if (!vec_remove(tok->tok_chars, i))
				exit_parser(tree, MSG_MALLOCF);
		}
		else
			i++;
	}
}
