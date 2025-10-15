/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:22:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/14 16:11:56 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <stdint.h>

void	ft_print_arena(const t_arena *arena)
{
	ft_printf("capacity: %u, size: %u, data ptr: %p\n",
		(uint32_t)arena->capacity, (uint32_t)arena->size, arena->data);
}

void	ft_print_arena_list(const t_arena *arena)
{
	t_arena	temp;
	int		i;

	temp = *arena;
	i = 1;
	ft_printf("ARENA %d ", i);
	ft_print_arena(&temp);
	while (temp.next)
	{
		temp = *temp.next;
		i++;
		ft_printf("ARENA %d ", i);
		ft_print_arena(&temp);
	}
}
