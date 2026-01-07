/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*  By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:45:20 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/07 17:13:51 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	exit_parser(t_tree *tree, char *error)
{
	clean(tree);
	if (error)
		perror(error);
	exit(EXIT_FAILURE);
}

void	clean(t_tree *tree)
{
	if (tree)
	{
		if (tree->a_buf)
			ft_arena_list_free(&tree->a_buf);
		if (tree->a_sys)
			ft_arena_list_free(&tree->a_sys);
	}
}
