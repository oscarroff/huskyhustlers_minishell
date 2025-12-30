/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 22:36:12 by thblack-          #+#    #+#             */
/*   Updated: 2025/12/30 23:46:16 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	val_cpy(char **val, const char *src, t_tree *tree)
{
	char	*tmp;
	char	quote;
	size_t	i;

	if (!val || !tree)
		return (FAIL);
	if (!src)
		return (SUCCESS);
	tmp = NULL;
	quote = 0;
	i = 0;
	if (*src == '"' || *src == '\'')
	{
		quote = *src;
		src++;
	}
	while (src[i] && src[i] != quote)
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
	if (i == 0 || !src[i])
		return (SUCCESS);
	if (!val_cpy(&val, src + i + 1, tree))
		return (FAIL);
	if (!envp_insert(tree, src, i, val))
		return (FAIL);
	return (SUCCESS);
}
