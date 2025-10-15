/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_basic_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:29:36 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/14 16:11:53 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <stdint.h>

t_arena	*ft_arena_init(size_t capacity)
{
	void	*data;
	t_arena	*arena;

	arena = malloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	data = malloc(sizeof(uint8_t) * capacity);
	if (!data)
	{
		free(arena);
		return (NULL);
	}
	arena->capacity = capacity;
	arena->size = 0;
	arena->next = NULL;
	arena->data = data;
	return (arena);
}

void	*ft_arena_alloc(t_arena *arena, size_t size)
{
	uint8_t	*data;
	t_arena	*current;
	t_arena	*next;

	current = arena;
	while (current->size + size >= current->capacity && current->next)
		current = current->next;
	if (current->size + size >= current->capacity)
	{
		current->size = current->capacity;
		if (size > ARENA_BUF)
			next = ft_arena_init(size);
		else
			next = ft_arena_init(ARENA_BUF);
		current->next = next;
		data = &next->data[0];
		next->size = size;
	}
	else
	{
		(void)next;
		data = &current->data[current->size];
		current->size += size;
	}
	return (data);
}

void	*ft_arena_reset(t_arena *arena)
{
	arena->size = 0;
	return (arena);
}

void	ft_arena_free(t_arena *arena)
{
	free(arena->data);
	free(arena);
}

void	ft_arena_list_free(t_arena *arena)
{
	t_arena	*current;
	t_arena	*next;

	current = arena;
	while (current)
	{
		next = current->next;
		ft_arena_free(current);
		current = next;
	}
}
