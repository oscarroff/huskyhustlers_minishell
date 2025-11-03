/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_push_pop_get.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:10:11 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/03 19:12:45 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <stdint.h>

int	vec_resize(t_vec *src, size_t target_capacity)
{
	uint8_t	*new;
	size_t	copy_len;

	if (!src || src->elem_size == 0
		|| target_capacity > SIZE_MAX / src->elem_size)
		return (-1);
	if (target_capacity == 0)
	{
		vec_reset(src);
		return (1);
	}
	new = malloc(target_capacity * src->elem_size);
	if (!new)
		return (-1);
	copy_len = src->len;
	if (copy_len > target_capacity)
		copy_len = target_capacity;
	if (copy_len > 0)
		ft_memcpy(new, (uint8_t *)src->data, copy_len * src->elem_size);
	free(src->data);
	src->data = new;
	src->len = copy_len;
	src->capacity = target_capacity;
	return (1);
}

static int	vec_check_and_grow(t_vec *dst, size_t extra)
{
	size_t	target_capacity;
	size_t	new_capacity;

	if (!dst || extra > SIZE_MAX - dst->len)
		return (-1);
	target_capacity = dst->len + extra;
	if (target_capacity <= dst->capacity)
		return (1);
	if (dst->capacity != 0)
		new_capacity = dst->capacity;
	else
		new_capacity = 1;
	while (new_capacity < target_capacity)
		new_capacity <<= 1;
	return (vec_resize(dst, new_capacity));
}

int	vec_push(t_vec *dst, const void *src)
{
	if (!dst || dst->elem_size == 0 || !src)
		return (-1);
	if (vec_check_and_grow(dst, 1) < 0)
		return (-1);
	ft_memcpy((uint8_t *)dst->data + dst->len * dst->elem_size,
		src, dst->elem_size);
	dst->len++;
	return (1);
}

int	vec_pop(void *dst, t_vec *src)
{
	size_t	new_capacity;

	if (!src || !src->data || src->elem_size == 0 || src->len == 0 || !dst)
		return (-1);
	src->len--;
	ft_memcpy(dst, (uint8_t *)src->data + src->len * src->elem_size,
		src->elem_size);
	new_capacity = src->capacity / 2;
	if (src->capacity > 1 && src->len <= src->capacity / 4)
	{
		if (new_capacity < 1)
			new_capacity = 1;
		if (vec_resize(src, new_capacity) < 0)
			return (-1);
	}
	return (1);
}

void	*vec_get(t_vec *src, size_t index)
{
	if (!src || !src->data || src->elem_size == 0 || index >= src->len)
		return (NULL);
	else
		return ((uint8_t *)src->data + index * src->elem_size);
}
