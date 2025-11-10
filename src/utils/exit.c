/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:45:20 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/10 12:23:02 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	clean_exit(t_tree *tree, char *error)
{
	if (tree)
		if (tree->arena)
			ft_arena_list_free(&tree->arena);
	if (error)
		ft_perror(error);
	exit(EXIT_FAILURE);
}

int	ft_perror(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	write(2, "\n", 1);
	return (FAIL);
}
