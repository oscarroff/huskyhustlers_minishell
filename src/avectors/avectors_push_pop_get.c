/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avectors_push_pop_get.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:10:11 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/03 12:17:07 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/avectors.h"
#include "../../inc/parsing.h"
#include "../../libft/inc/libft.h"

int	avec_resize(t_avec *src, size_t target_size)
{
	t_avec	*dst;

	if (!src || !src->data)
		return (-1);
	if (avec_new(dst, (target_size / src->elem_size), src->arena) < 0)
		return (-1);
	if (avec_copy(dst, src) < 0)
	{
		avec_free(dst);
		return (-1);
	}
	avec_free(src);
	*src = *dst;
	return (1);
}

int	avec_push(t_avec *dst, void *src)
{
	if (!dst || !dst->data || dst->elem_size == 0 || !src)
		return (-1);
	if (dst->len + 1 >= dst->alloc_size / dst->elem_size)
		if (avec_resize(dst, dst->alloc_size * 2) < 0)
			return (-1);
	ft_memcpy(dst->data + dst->len * dst->elem_size,
		src, dst->elem_size);
	dst->len++;
	return (1);
}

int	avec_pop(void *dst, t_avec *src)
{
	if (!src || !src->data || src->elem_size == 0 || src->len == 0 || !dst)
		return (-1);
	src->len--;
	ft_memcpy(dst, src->data + src->len * src->elem_size, src->elem_size);
	if (src->len < (src->alloc_size / src->elem_size) / 2)
		return (avec_resize(src, src->alloc_size / 2));
	return (1);
}

void	*avec_get(t_avec *src, size_t index)
{
	if (!src || !src->data || src->len == 0 || src->elem_size == 0
		|| index >= src->len)
		return (NULL);
	else
		return (&src->data[index * src->elem_size]);
}
