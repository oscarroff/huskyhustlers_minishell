/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_middle_and_end.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:17:15 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/15 18:25:47 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	vec_insert(t_vec *dst, void *src, size_t index)
{
	if (index > dst->len || !dst || !dst->data || !src)
		return (-1);
	if (dst->len + 1 >= dst->alloc_size / dst->elem_size)
		vec_resize(dst, dst->alloc_size * 2);
	ft_memmove(dst->data + (index + 1) * dst->elem_size,
		dst->data + index * dst->elem_size,
		(dst->len - index) * dst->elem_size);
	ft_memcpy(dst->data + index * dst->elem_size, src, dst->elem_size);
	dst->len++;
	return (1);
}

int	vec_remove(t_vec *src, size_t index)
{
	if (!src || !src->data || src->elem_size == 0 || src->len == 0)
		return (-1);
	ft_memmove(src->data + index * src->elem_size,
		src->data + (index + 1) * src->elem_size,
		(src->len - index) * src->elem_size);
	src->len--;
	if (src->len < (src->alloc_size / src->elem_size) / 2)
		if (vec_resize(src, src->alloc_size / 2) < 0)
			return (-1);
	return (1);
}

static int	vec_pend(t_vec *dst, t_vec *src)
{
	if (!dst || !dst->data || dst->elem_size == 0
		|| dst->elem_size != src->elem_size)
		return (-1);
	if (!src || !src->data || src->len == 0 || src->elem_size == 0)
		return (1);
	if ((dst->len + src->len) * dst->elem_size >= dst->alloc_size)
	{
		if (dst->len >= src->len)
			if (vec_resize(dst, dst->len * dst->elem_size * 4) < 0)
				return (-1);
		if (dst->len < src->len)
			if (vec_resize(dst, src->len * dst->elem_size * 4) < 0)
				return (-1);
	}
	return (1);
}

int	vec_append(t_vec *dst, t_vec *src)
{
	if (vec_pend(dst, src) < 0)
		return (-1);
	ft_memcpy(dst->data + dst->len * dst->elem_size, src->data, src->len
		* dst->elem_size);
	dst->len += src->len;
	return (1);
}

int	vec_prepend(t_vec *dst, t_vec *src)
{
	if (vec_pend(dst, src) < 0)
		return (-1);
	ft_memmove(dst->data + dst->len * dst->elem_size, dst->data, dst->len
		* dst->elem_size);
	ft_memcpy(dst->data, src->data, src->len * dst->elem_size);
	dst->len += src->len;
	return (1);
}
