/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_push_pop_get.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:10:11 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/15 18:26:04 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	vec_resize(t_vec *src, size_t target_size)
{
	t_vec	dst;

	if (!src || !src->data)
		return (-1);
	if (vec_new(&dst, (target_size / src->elem_size), src->elem_size) < 0)
		return (-1);
	if (vec_copy(&dst, src) < 0)
	{
		vec_free(&dst);
		return (-1);
	}
	vec_free(src);
	*src = dst;
	return (1);
}

int	vec_push(t_vec *dst, void *src)
{
	if (!dst || !dst->data || dst->elem_size == 0 || !src)
		return (-1);
	if (dst->len + 1 >= dst->alloc_size / dst->elem_size)
		if (vec_resize(dst, dst->alloc_size * 2) < 0)
			return (-1);
	ft_memcpy(dst->data + dst->len * dst->elem_size,
		src, dst->elem_size);
	dst->len++;
	return (1);
}

int	vec_pop(void *dst, t_vec *src)
{
	if (!src || !src->data || src->elem_size == 0 || src->len == 0 || !dst)
		return (-1);
	src->len--;
	ft_memcpy(dst, src->data + src->len * src->elem_size, src->elem_size);
	if (src->len < (src->alloc_size / src->elem_size) / 2)
		return (vec_resize(src, src->alloc_size / 2));
	return (1);
}

void	*vec_get(t_vec *src, size_t index)
{
	if (!src || !src->data || src->len == 0 || src->elem_size == 0
		|| index > src->len)
		return (NULL);
	else
		return (&src->data[index * src->elem_size]);
}
