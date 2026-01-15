/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 22:36:12 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/15 15:04:13 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	val_cpy(char **val, const char *src, t_tree *tree)
{
	char	*tmp;
	size_t	i;

	if (!val || !tree)
		return (FAIL);
	if (!src)
	{
		if (!ft_superstrdup(&tmp, "", tree->a_sys))
			return (FAIL);
		return (SUCCESS);
	}
	tmp = NULL;
	i = 0;
	while (src[i])
		i++;
	if (!ft_superstrndup(&tmp, src, i, tree->a_sys))
		return (FAIL);
	*val = tmp;
	return (SUCCESS);
}

int	envp_set(t_tree *tree, const char *src)
{
	size_t	i;
	char	*val;

	if (!tree || !tree->envp || !tree->a_sys)
		return (FAIL);
	if (!src)
		return (SUCCESS);
	i = 0;
	val = NULL;
	while (src[i] && src[i] != '=')
		i++;
	if (!src[i])
	{
		if (!envp_insert(tree, src, i, NULL))
			return (FAIL);
		return (SUCCESS);
	}
	if (!val_cpy(&val, src + i + 1, tree))
		return (FAIL);
	if (!envp_insert(tree, src, i, val))
		return (FAIL);
	return (SUCCESS);
}
