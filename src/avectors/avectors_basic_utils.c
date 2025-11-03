/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avectors_basic_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:23:38 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/03 12:06:04 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/avectors.h"
#include "../../inc/parsing.h"
#include "../../libft/inc/libft.h"

void	avec_init(t_avec *dst, size_t init_len, t_arena *arena)
{
	dst->elem_size = sizeof(void *);
	dst->alloc_size = init_len * dst->elem_size;
	dst->len = 0;
}

int	avec_new(t_avec *dst, size_t init_len, t_arena *arena)
{
	if (!arena)
		return (-1);
	if (init_len == 0)
	{
		dst->data = NULL;
		return (1);
	}
	if (!ft_arena_alloc(arena, (void **)dst, sizeof(t_avec)))
		return (error_msg(ERR_MALLOCF));
	avec_init(dst, init_len, arena);
	if (!ft_arena_alloc(arena, (void **)dst->data, sizeof(void *)))
		return (error_msg(ERR_MALLOCF));
	if (!dst->data)
		return (-1);
	return (1);
}

void	avec_free(t_avec *src)
{
	src->data = NULL;
	src->alloc_size = 0;
	src->elem_size = 0;
	src->len = 0;
}

int	avec_from(t_avec *dst, void *src, t_arena *arena)
{
	if (!src)
		return (-1);
	if (avec_new(dst, 1, arena) == -1)
		return (-1);
	ft_memcpy(dst->data, src, sizeof(void *));
	dst->len = 1;
	return (1);
}

int	avec_copy(t_avec *dst, t_avec *src)
{
	size_t	n;
	size_t	dst_cap;

	if (dst == src || dst->elem_size != src->elem_size || dst->elem_size == 0
		|| src->elem_size == 0 || !dst->data || !src->data)
		return (-1);
	n = src->len;
	dst_cap = dst->alloc_size / dst->elem_size;
	if (dst->len + n > dst_cap)
		n = dst_cap - dst->len;
	ft_memcpy((void *)dst->data + dst->len * dst->elem_size,
		(void *)src->data, n * dst->elem_size);
	dst->len += n;
	return (1);
}
