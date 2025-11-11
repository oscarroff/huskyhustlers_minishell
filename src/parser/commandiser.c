/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:03:45 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/10 12:22:48 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

// TODO: Implement copy functions to transfer tokens to tree one by one

static void	init_cmd_table(t_tree *tree);
// static void	parse_word(t_tree *tree, t_token *token);

void	commandise(t_tree *tree, t_token *tok)
{
	if (!tree || !tok)
		return ;
	if (!tree->cmd_tab)
		init_cmd_table(tree);
	// ft_print_arena_list(tree->arena);
	// ft_printf("ptr: %p\n", tree->cmd_tab);
	// if (ft_arena_alloc(tree->arena,
	// 	(void **)tree->cmd_tab->data, sizeof(t_cmd)))
	// 	return (clean_exit(tree, MSG_MALLOCF));
	// if (token->type == TOK_WORD || token->type == TOK_QUOTATION)
	// 	parse_word(tree, token);
	// if (token->type == TOK_REDIRECT)
	// 	parse_redirect(tree, token);
}

static void	init_cmd_table(t_tree *tree)
{
	// ft_printf("I got here\n");
	if (!vec_alloc(&tree->cmd_tab, tree->arena))
		return (clean_exit(tree, MSG_MALLOCF));
	vec_init(tree->cmd_tab, 0, sizeof(t_cmd), tree->arena);
}

// static void	parse_word(t_tree *tree, t_token *token)
// {
// 	(void)tree;
// 	(void)token;
// }
