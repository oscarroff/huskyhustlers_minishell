/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 21:21:45 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/16 13:30:11 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	envp_search(t_tree *tree, const char *find, size_t len, size_t *key_i);
int	envp_edit(t_tree *tree, size_t key_index, char *val);

int	envp_insert(t_tree *tree, const char *key, size_t len, char *val)
{
	size_t	key_i;

	if (!tree || !key)
		return (FAIL);
	key_i = 0;
	if (envp_search(tree, key, len, &key_i))
	{
		if (!envp_edit(tree, key_i, val))
			return (FAIL);
	}
	else
	{
		if (!envp_add(tree, key, len, val))
			return (FAIL);
	}
	return (SUCCESS);
}

int	envp_search(t_tree *tree, const char *find, size_t len, size_t *key_i)
{
	t_keyval	*tmp;
	size_t		i;

	if (!tree || !tree->envp || tree->envp->len == 0
		|| len == 0 || !find || !key_i)
		return (FAIL);
	i = 0;
	while (i < tree->envp->len)
	{
		tmp = *(t_keyval **)vec_get(tree->envp, i);
		if (ft_strncmp(tmp->key, find, len) == 0 && !tmp->key[len])
		{
			*key_i = i;
			return (SUCCESS);
		}
		i++;
	}
	return (FAIL);
}

int	envp_edit(t_tree *tree, size_t key_index, char *val)
{
	t_keyval	*tmp;

	if (!tree || !tree->envp || !key_index)
		return (FAIL);
	tmp = *(t_keyval **)vec_get(tree->envp, key_index);
	tmp->value = val;
	return (SUCCESS);
}

int	envp_add(t_tree *tree, const char *key, size_t len, char *val)
{
	t_keyval	*tmp;

	if (!tree || !tree->envp || !key)
		return (FAIL);
	tmp = NULL;
	envp_key_value_init(&tmp, tree);
	if (!ft_superstrndup(&tmp->key, key, len, tree->a_sys))
		return (FAIL);
	tmp->value = val;
	if (!vec_push(tree->envp, &tmp))
		return (FAIL);
	return (SUCCESS);
}
