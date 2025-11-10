/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:41:21 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/10 12:23:04 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int	parser(t_tree *tree, char *line)
{
	t_token	*token;

	if (!tree || !line)
		return (FAIL);
	token = NULL;
	if (!valid_input(line))
		return (FAIL);
	init_lexer(&token, tree);
	while (line && *line && *line != '\0')
	{
		while (ft_isspace(*line))
			line++;
		if (!*line)
			break ;
		tokenise(token, line, tree);
		if (token->tok_chars)
			vec_printf_s(token->tok_chars);
		// ft_printf("Read size: %u\n", (uint32_t)token->read_size);
		if (token->expand == true)
		{
			expandise(token, tree);
			vec_printf_s(token->tok_chars);
		}
		commandise(tree, token);
		line += token->read_size;
		vec_reset(token->tok_chars);
	}
	return (SUCCESS);
}

void	init_lexer(t_token **token, t_tree *tree)
{
	t_token	*new;

	if (!token || !tree)
		clean_exit(tree, MSG_UNITIAL);
	if (!ft_arena_init(&tree->arena, ARENA_BUF))
		clean_exit(tree, "malloc fail 2");
	if (!ft_arena_alloc(tree->arena, (void **)token, sizeof(t_token)))
		clean_exit(tree, "malloc fail 3");
	new = *token;
	if (!vec_alloc(&new->tok_chars, tree->arena))
		clean_exit(tree, "malloc fail 4");
	new->type = TOK_DEFAULT;
	new->redirect = RDR_DEFAULT;
	new->quote = '\0';
	new->expand = false;
	new->read_size = 1;
}
