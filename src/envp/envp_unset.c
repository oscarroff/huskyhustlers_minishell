/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:23:23 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/02 16:27:22 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	envp_unset(t_tree *tree, const char *src)
{
	size_t	key_i;

	if (!tree)
		return (FAIL);
	if (!src)
		return (SUCCESS);
	key_i = 0;
	if (envp_search(tree, src, ft_strlen(src), &key_i))
	{
		if (!vec_remove(tree->envp, key_i))
			return (FAIL);
	}
	return (SUCCESS);
}
