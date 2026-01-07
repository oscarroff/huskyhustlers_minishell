/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:33:02 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/07 14:31:09 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <stdint.h>

void	vec_init(t_vec *dst, size_t init_len, size_t elem_size, t_arena *arena)
{
	if (!dst)
		return ;
	dst->len = 0;
	dst->elem_size = elem_size;
	dst->capacity = init_len;
	dst->data = NULL;
	dst->arena = arena;
}

void	vec_set(t_vec *dst, uint8_t *data, size_t len, size_t capacity)
{
	if (!dst)
		return ;
	dst->data = data;
	dst->len = len;
	dst->capacity = capacity;
}

int	vec_exit(t_vec *dst)
{
	dst->capacity = 0;
	dst->elem_size = 0;
	return (FAIL);
}

int	vec_safe_size(size_t a, size_t b, size_t *dst)
{
	if (b != 0 && a > SIZE_MAX / b)
		return (ft_errno_set(EINVAL, FAIL));
	*dst = a * b;
	return (SUCCESS);
}

int	ft_memcpy_safe(void *dst, const void *src, size_t len, size_t size)
{
	size_t	copy_bytes;

	if (!vec_safe_size(len, size, &copy_bytes))
		return (FAIL);
	ft_memcpy(dst, src, copy_bytes);
	return (SUCCESS);
}
