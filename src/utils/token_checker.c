/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:53:16 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 15:13:59 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/parsing.h"

// void	token_checker(t_tree *tree, t_vec *tokens, size_t i, size_t argc)
// {
// 	t_token	*tmp;
//
// 	(void)argc;
// 	(void)tree;
// 	while (i < tokens->len)
// 	{
// 		tmp = *(t_token **)vec_get(tokens, i);
// 		if (tmp->type == TOK_PIPE)
// 			break ;
// 		if (tmp->type == TOK_REDIRECT)
// 		{
// 			ft_printf("Redirect found\n");
// 			i++;
// 			// i += parse_io(tree, tokens, i);
// 		}
// 		if (tmp->type == TOK_IO)
// 		{
// 			ft_printf("I/O found\n");
// 			i++;
// 			// i += parse_io(tree, tokens, i);
// 		}
// 		else if (tmp->type == TOK_WORD || tmp->type == TOK_QUOTATION)
// 		{
// 			ft_printf("Word found\n");
// 			i++;
// 			// i += parse_argv(tree, tokens, i, argc);
// 		}
// 	}
// }
//
