/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:47:54 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/07 15:56:57 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	ft_perror(t_tree *tree, char *s)
{
	try_write(tree, STDERR_FILENO, "minishell: ");
	try_write_endl(tree, STDERR_FILENO, s);
	return (FAIL);
}

int	ft_parse_error(t_tree *tree, char *s)
{
	if (s)
	{
		try_write(tree, STDERR_FILENO, "minishell: ");
		if (s)
		{
			try_write(tree, STDERR_FILENO, s);
			try_write(tree, STDERR_FILENO, " ");
		}
	}
	try_write_endl(tree, STDERR_FILENO, strerror(errno));
	return (FAIL);
}

int	ft_parse_warn(char *s)
{
	try_write(NULL, STDERR_FILENO, "minishell: ");
	if (s)
		try_write_endl(NULL, STDERR_FILENO, s);
	else
		try_write_endl(NULL, STDERR_FILENO, "error undefined");
	return (FAIL);
}
