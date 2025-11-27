/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:45:20 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 20:38:25 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_parser(t_tree *tree, char *error)
{
	if (tree)
	{
		if (tree->a_buf)
			ft_arena_list_free(&tree->a_buf);
		if (tree->a_sys)
			ft_arena_list_free(&tree->a_sys);
	}
	if (error)
		perror(error);
	exit(EXIT_FAILURE);
}
