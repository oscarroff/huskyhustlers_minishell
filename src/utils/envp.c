/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:39:44 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/18 17:07:51 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include "../../inc/minishell.h"
#include <stdint.h>

static int	envp_export_helper(char **dst, const t_keyval *src, t_arena *arena)
{
	char	*new;
	size_t	key_len;
	size_t	value_len;

	new = NULL;
	if (!dst || !arena)
		return (FAIL);
	if (!src)
		return (SUCCESS);
	key_len = ft_strlen(src->key);
	value_len = ft_strlen(src->value);
	if (!ft_arena_alloc(arena, (void **)&new, key_len + value_len + 2))
		return (FAIL);
	ft_memcpy(new, src->key, key_len);
	new[key_len] = '=';
	ft_memcpy(new + key_len + 1, src->value, value_len);
	new[key_len + value_len + 1] = '\0';
	*dst = new;
	return (SUCCESS);
}

int	envp_export(char ***dst, t_tree *tree)
{
	char	**new;
	size_t	i;

	new = NULL;
	i = 0;
	if (!dst || !tree)
		return (FAIL);
	if (!tree->envp || tree->envp->len == 0)
		return (SUCCESS);
	if (!ft_arena_alloc(tree->arena, (void **)&new,
			(tree->envp->len + 1) * sizeof(char *)))
		return (FAIL);
	while (i < tree->envp->len)
	{
		new[i] = NULL;
		if (!envp_export_helper(&new[i],
				*(const t_keyval **)vec_get(tree->envp, i), tree->arena))
			return (FAIL);
		i++;
	}
	new[i] = NULL;
	*dst = new;
	return (SUCCESS);
}

char	*envp_get(char *find, t_tree *tree)
{
	t_keyval	*tmp;
	size_t		i;

	if (!find)
		return (NULL);
	i = 0;
	while (i < tree->envp->len)
	{
		tmp = *(t_keyval **)vec_get(tree->envp, i);
		if (ft_strcmp(tmp->key, find) == 0)
			return (tmp->value);
		i++;
	}
	return (NULL);
}
