/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:11:24 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/19 14:14:17 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	expand_exit_code(t_vec *tmp, t_parse *p, size_t i, t_tree *tree)
{
	char	*num;

	num = NULL;
	if (!ft_superitoa(&num, tree->exit_code, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	vec_reset(tmp);
	if (!vec_from(tmp, num, ft_strlen(num), sizeof(char)))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_inpend(p->tok->tok_chars, tmp, i))
		exit_parser(tree, MSG_MALLOCF);
	return (SUCCESS);
}

int	expand_valid(char *src, size_t i, char quote_char)
{
	if (src[i] == '$' && quote_char != '\'' && (src[i + 1] == '?'
			|| src[i + 1] == '_' || ft_isalpha(src[i + 1])
			|| src[i + 1] == '\''
			|| (src[i + 1] == '"' && quote_char != '"')))
		return (SUCCESS);
	return (FAIL);
}

int	expand_init(t_token *tok)
{
	if (!tok || !tok->tok_chars || tok->tok_chars->len == 0
		|| (tok->redirect == RDR_HEREDOC && tok->quote_type != QUO_DEFAULT))
		return (FAIL);
	return (SUCCESS);
}
