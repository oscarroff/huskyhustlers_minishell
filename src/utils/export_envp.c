/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:39:44 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/17 23:25:21 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include "../../inc/minishell.h"
#include <stdint.h>

static int	export_envp_helper(char **dst, const t_keyval *src, t_arena *arena)
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

int	export_envp(char ***dst, t_vec *envp, t_arena *arena)
{
	char	**new;
	size_t	i;

	new = NULL;
	i = 0;
	if (!dst || !arena)
		return (FAIL);
	if (!envp || envp->len == 0)
		return (SUCCESS);
	if (!ft_arena_alloc(arena, (void **)&new, (envp->len + 1) * sizeof(char *)))
		return (FAIL);
	while (i < envp->len)
	{
		new[i] = NULL;
		if (!export_envp_helper(&new[i],
				*(const t_keyval **)vec_get(envp, i), arena))
			return (FAIL);
		i++;
	}
	new[i] = NULL;
	*dst = new;
	return (SUCCESS);
}
