/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:05:28 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/03 19:14:45 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static void	vec_printf_s(const t_vec *src)
{
	write(1, "Data: ", 6);
	write(1, (char *)src->data, src->len);
	write(1, "\n", 1);
}

static void	vec_printf_array(const t_vec *src, char c)
{
	size_t	i;

	i = 0;
	while (i < src->len)
	{
		if (c == 'c')
			ft_printf("Data[%u]: %c\n", (uint32_t)i,
				((char *)src->data)[i]);
		if (c == 'p')
			ft_printf("Data[%u]: %p\n", (uint32_t)i,
				((unsigned long *)src->data)[i]);
		if (c == 'd')
			ft_printf("Data[%u]: %d\n", (uint32_t)i,
				((int *)src->data)[i]);
		if (c == 'u')
			ft_printf("Data[%u]: %u\n", (uint32_t)i,
				((uint32_t *)src->data)[i]);
		if (c == 'x')
			ft_printf("Data[%u]: %x\n", (uint32_t)i,
				((unsigned long *)src->data)[i]);
		if (c == 'X')
			ft_printf("Data[%u]: %X\n", (uint32_t)i,
				((unsigned long *)src->data)[i]);
		i++;
	}
}

void	vec_printf(const t_vec *src, char c)
{
	size_t	i;

	i = 0;
	if (!src)
		return ;
	ft_printf("VECTOR DATA\ncapacity: %u elem_size: %u len: %u\n",
		(uint32_t)src->capacity, (uint32_t)src->elem_size,
		(uint32_t)src->len);
	if (!src->data)
		return ;
	if (c == 'c' || c == 'p' || c == 'd' || c == 'i' || c == 'u' || c == 'x'
		|| c == 'X')
		vec_printf_array(src, c);
	if (c == 's')
		vec_printf_s(src);
}
