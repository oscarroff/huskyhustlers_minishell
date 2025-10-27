/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:22:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/27 16:58:52 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_print_arena(const t_arena *arena)
{
	ft_printf("capacity: %u, size: %u, data ptr: %p\n",
		(u_int32_t)arena->capacity, (u_int32_t)arena->size, arena->data);
}

void	ft_print_arena_list(const t_arena *arena)
{
	t_arena	current;
	int		i;

	current = *arena;
	i = 1;
	ft_printf("ARENA %d ", i);
	ft_print_arena(&current);
	while (current.next)
	{
		current = *current.next;
		i++;
		ft_printf("ARENA %d ", i);
		ft_print_arena(&current);
	}
}
