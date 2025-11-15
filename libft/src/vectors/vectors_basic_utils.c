/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_basic_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:23:38 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/03 19:14:11 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <stddef.h>

int	vec_new(t_vec *dst, size_t init_len, size_t elem_size)
{
	if (elem_size == 0)
		return (-1);
	dst->capacity = init_len;
	dst->elem_size = elem_size;
	dst->len = 0;
	if (init_len == 0)
	{
		dst->data = NULL;
		return (1);
	}
	dst->data = malloc(elem_size * init_len);
	if (!dst->data)
	{
		dst->capacity = 0;
		dst->elem_size = 0;
		return (-1);
	}
	return (1);
}

void	vec_free(t_vec *src)
{
	if (!src)
		return ;
	free(src->data);
	src->data = NULL;
	src->capacity = 0;
	src->elem_size = 0;
	src->len = 0;
}

void	vec_reset(t_vec *src)
{
	if (!src)
		return ;
	free(src->data);
	src->data = NULL;
	src->capacity = 0;
	src->len = 0;
}

int	vec_from(t_vec *dst, void *src, size_t len, size_t elem_size)
{
	if (!src || len == 0 || elem_size == 0)
		return (-1);
	if (vec_new(dst, len, elem_size) == -1)
		return (-1);
	if (len > 0)
		ft_memcpy(dst->data, src, len * elem_size);
	dst->len = len;
	return (1);
}

int	vec_copy(t_vec *dst, t_vec *src)
{
	size_t	n;
	size_t	dst_cap;

	if (dst == src || dst->elem_size != src->elem_size || dst->elem_size == 0
		|| src->elem_size == 0 || !dst->data || !src->data)
		return (-1);
	n = src->len;
	dst_cap = dst->capacity / dst->elem_size;
	if (dst->len + n > dst_cap)
		n = dst_cap - dst->len;
	ft_memcpy((uint8_t *)dst->data + dst->len * dst->elem_size,
		(uint8_t *)src->data, n * dst->elem_size);
	dst->len += n;
	return (1);
}
