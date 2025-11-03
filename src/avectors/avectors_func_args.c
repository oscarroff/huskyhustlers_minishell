/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avectors_func_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:51:33 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/03 12:21:48 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/avectors.h"
#include "../../inc/parsing.h"
#include "../../libft/inc/libft.h"

int	avec_iter(t_avec *src, void (*f)(void *))
{
	size_t	i;

	i = 0;
	if (!src || !src->data || src->elem_size == 0 || src->len == 0 || !f)
		return (-1);
	while (i < src->len)
		(f)(src->data + src->elem_size * i++);
	return (1);
}

int	avec_map(t_avec *dst, t_avec *src, void (*f)(void *))
{
	if (!src || !dst || dst == src || src->elem_size == 0 || !src->data || !f)
		return (-1);
	if (src->len * src->elem_size > dst->alloc_size)
	{
		if (!dst->data)
		{
			if (avec_new(dst, src->len, src->arena) < 0)
				return (-1);
		}
		else
			if (avec_resize(dst, src->len))
				return (-1);
	}
	if (avec_copy(dst, src) < 0)
		return (-1);
	if (avec_iter(dst, f) < 0)
		return (-1);
	return (1);
}

int	avec_filter(t_avec *dst, t_avec *src, bool (*f)(void *))
{
	size_t	i;

	i = 0;
	if (!src || !dst || dst == src || src->elem_size == 0 || !src->data || !f)
		return (-1);
	while (i < src->len)
	{
		if (f(src->data + i * src->elem_size) == true)
			if (avec_push(dst, src->data + i * src->elem_size) < 0)
				return (-1);
		i++;
	}
	return (1);
}

int	avec_reduce(void *acc, t_avec *src, void (*f)(void *, void *))
{
	size_t	i;

	i = 0;
	if (!acc || !src || src->elem_size == 0 || !src->data || !f)
		return (-1);
	while (i < src->len)
		f(acc, src->data + src->elem_size * i++);
	return (1);
}
