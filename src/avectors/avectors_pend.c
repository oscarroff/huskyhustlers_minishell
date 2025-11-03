/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avectors_pend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:10:12 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/03 12:07:37 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/avectors.h"
#include "../../inc/parsing.h"
#include "../../libft/inc/libft.h"

static int	avec_pend(t_avec *dst, t_avec *src)
{
	if (!dst || !dst->data || dst->elem_size == 0
		|| dst->elem_size != src->elem_size
		|| !src || !src->data || src->len == 0 || src->elem_size == 0)
		return (-1);
	if ((dst->len + src->len) * dst->elem_size >= dst->alloc_size)
	{
		if (dst->len >= src->len)
			if (avec_resize(dst, dst->len * dst->elem_size * 4) < 0)
				return (-1);
		if (dst->len < src->len)
			if (avec_resize(dst, src->len * dst->elem_size * 4) < 0)
				return (-1);
	}
	return (1);
}

int	avec_append(t_avec *dst, t_avec *src)
{
	if (avec_pend(dst, src) < 0)
		return (-1);
	ft_memcpy(dst->data + dst->len * dst->elem_size, src->data, src->len
		* dst->elem_size);
	dst->len += src->len;
	return (1);
}

int	avec_prepend(t_avec *dst, t_avec *src)
{
	if (avec_pend(dst, src) < 0)
		return (-1);
	ft_memmove(dst->data + src->len * dst->elem_size, dst->data, dst->len
		* dst->elem_size);
	ft_memcpy(dst->data, src->data, src->len * dst->elem_size);
	dst->len += src->len;
	return (1);
}

int	avec_inpend(t_avec *dst, t_avec *src, size_t after)
{
	if (after < 0 || after > dst->len)
		return (-1);
	if (avec_pend(dst, src) < 0)
		return (-1);
	ft_memmove(dst->data + (after + src->len) * dst->elem_size,
		dst->data + after * dst->elem_size,
		(dst->len - after) * dst->elem_size);
	ft_memcpy(dst->data + after * dst->elem_size,
		src->data, src->len * dst->elem_size);
	dst->len += src->len;
	return (1);
}
