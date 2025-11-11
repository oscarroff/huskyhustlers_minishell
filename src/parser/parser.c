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

void	token_reset(t_token *token);

static void	init_lexer(t_token **token, t_tree *tree);
static bool	ft_nothingtodo(char **line);

int	parser(t_tree *tree, char *line)
{
	t_token	*token;
	// e_syntax	syntax;

	if (!tree || !line)
		return (FAIL);
	if (!valid_input(line))
		return (FAIL);
	if (ft_nothingtodo(&line))
		return (SUCCESS);
	token = NULL;
	// syntax = SYN_DEFAULT;
	init_lexer(&token, tree);
	while (*line)
	{
		tokenise(token, line, tree);
		if (token->expand == true)
			expandise(token, tree);
		vec_printf_s(token->tok_chars);
		line += token->read_size;
	}
	// commandise(tree, token);
	return (SUCCESS);
}

// void	token_reset(t_token *token)
// {
// 	vec_reset(token->tok_chars);
// 	token->type = TOK_DEFAULT;
// 	token->redirect = RDR_DEFAULT;
// 	token->quote = '\0';
// 	token->expand = false;
// 	token->read_size = 1;
// }

static bool	ft_nothingtodo(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (!**line)
		return (true);
	return (false);
}

static void	init_lexer(t_token **token, t_tree *tree)
{
	t_token	*new;

	if (!token || !tree)
		clean_exit(tree, MSG_UNINTAL);
	if (*token)
		return ;
	if (!ft_arena_init(&tree->arena, ARENA_BUF))
		clean_exit(tree, "malloc fail 2");
	if (!ft_arena_alloc(tree->arena, (void **)token, sizeof(t_token)))
		clean_exit(tree, "malloc fail 3");
	new = *token;
	new->tok_chars = NULL;
	if (!vec_alloc(&new->tok_chars, tree->arena))
		clean_exit(tree, "malloc fail 4");
	new->type = TOK_DEFAULT;
	new->redirect = RDR_DEFAULT;
	new->quote = '\0';
	new->expand = false;
	new->read_size = 1;
}
