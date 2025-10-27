/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_pend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:10:12 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/27 14:36:48 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	vec_pend(t_vec *dst, t_vec *src)
{
	if (!dst || !dst->data || dst->elem_size == 0
		|| dst->elem_size != src->elem_size
		|| !src || !src->data || src->len == 0 || src->elem_size == 0)
		return (-1);
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
	ft_memmove(dst->data + src->len * dst->elem_size, dst->data, dst->len
		* dst->elem_size);
	ft_memcpy(dst->data, src->data, src->len * dst->elem_size);
	dst->len += src->len;
	return (1);
}

int	vec_inpend(t_vec *dst, t_vec *src, size_t after)
{
	if (after < 0 || after > dst->len)
		return (-1);
	if (vec_pend(dst, src) < 0)
		return (-1);
	ft_memmove(dst->data + (after + src->len) * dst->elem_size,
		dst->data + after * dst->elem_size,
		(dst->len - after) * dst->elem_size);
	ft_memcpy(dst->data + after * dst->elem_size,
		src->data, src->len * dst->elem_size);
	dst->len += src->len;
	return (1);
}
