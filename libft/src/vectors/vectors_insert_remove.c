/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_insert_remove.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:17:15 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/27 14:18:13 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <stdint.h>

int	vec_insert(t_vec *dst, void *src, size_t index)
{
	size_t	offset;
	size_t	offset_bytes;

	if (!src || !dst)
		return (FAIL);
	if (index > dst->len || !dst->data)
		return (FAIL);
	if (!vec_check_and_grow(dst, 1))
		return (FAIL);
	offset = dst->len - index;
	if (offset > 0)
	{
		if (!vec_safe_size(offset, dst->elem_size, &offset_bytes))
			return (FAIL);
		ft_memmove((uint8_t *)dst->data + (index + 1) * dst->elem_size,
			(uint8_t *)dst->data + index * dst->elem_size, offset_bytes);
	}
	ft_memcpy((uint8_t *)dst->data + index * dst->elem_size, src,
		dst->elem_size);
	dst->len++;
	return (SUCCESS);
}

int	vec_remove(t_vec *src, size_t index)
{
	size_t	offset;
	size_t	offset_bytes;

	if (!src)
		return (FAIL);
	if (!src->data || src->elem_size == 0 || src->len == 0 || index >= src->len)
		return (FAIL);
	if (index + 1 >= src->len)
		offset = 0;
	else
		offset = src->len - index - 1;
	if (offset > 0)
	{
		if (!vec_safe_size(offset, src->elem_size, &offset_bytes))
			return (FAIL);
		ft_memmove((uint8_t *)src->data + index * src->elem_size,
			(uint8_t *)src->data + (index + 1) * src->elem_size, offset_bytes);
	}
	src->len--;
	if (src->capacity >= 2 && src->len <= src->capacity / 4)
		if (!vec_resize(src, src->capacity / 2))
			return (FAIL);
	return (SUCCESS);
}

static int	trim_helper(t_vec *src, size_t index, size_t len, size_t tail_len)
{
	size_t	tail_bytes;
	size_t	offset_bytes;
	size_t	trim_bytes;

	if (!vec_safe_size(tail_len, src->elem_size, &tail_bytes)
		|| !vec_safe_size(index, src->elem_size, &offset_bytes)
		|| !vec_safe_size(len, src->elem_size, &trim_bytes))
		return (FAIL);
	ft_memmove((uint8_t *)src->data + offset_bytes,
		(uint8_t *)src->data + offset_bytes + trim_bytes, tail_bytes);
	return (SUCCESS);
}

int	vec_trim(t_vec *src, size_t index, size_t len)
{
	size_t	tail_len;

	if (!src || !src->data || src->elem_size == 0 || src->len == 0
		|| index >= src->len || len > src->len - index)
		return (FAIL);
	if (len == 0)
		return (SUCCESS);
	if (index + len >= src->len)
		tail_len = 0;
	else
		tail_len = src->len - index - len;
	if (tail_len > 0)
		trim_helper(src, index, len, tail_len);
	src->len -= len;
	if (src->capacity >= 2 && src->len <= src->capacity / 4)
		if (!vec_resize(src, src->capacity / 2))
			return (FAIL);
	return (SUCCESS);
}
