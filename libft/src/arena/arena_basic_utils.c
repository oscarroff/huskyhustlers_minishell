/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_basic_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:29:36 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/27 16:56:09 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_arena_init(t_arena **arena, size_t capacity)
{
	t_arena	*new;

	if (!arena || capacity == 0)
		return (-1);
	new = malloc(sizeof(t_arena));
	if (!new)
		return (-1);
	new->data = malloc(sizeof(uint8_t) * capacity);
	if (!new->data)
	{
		free(new);
		return (-1);
	}
	new->capacity = capacity;
	new->size = 0;
	new->next = NULL;
	*arena = new;
	return (1);
}

int	ft_arena_alloc(t_arena *arena, void *ptr, size_t size)
{
	t_arena	*current;
	t_arena	*next;
	size_t	capacity;

	if (!arena || !arena->data || size == 0)
		return (-1);
	current = arena;
	capacity = size;
	while (current->size + size >= current->capacity && current->next)
		current = current->next;
	if (current->size + size >= current->capacity)
	{
		current->size = current->capacity;
		if (capacity < ARENA_BUF)
			capacity = ARENA_BUF;
		if (ft_arena_init(&next, capacity) < 0)
			return (-1);
		current->next = next;
		current = current->next;
	}
	ptr = &current->data[current->size];
	current->size += size;
	return (1);
}

int	ft_arena_reset(t_arena *arena)
{
	if (!arena)
		return (-1);
	arena->size = 0;
	return (1);
}

int	ft_arena_free(t_arena **arena)
{
	t_arena	*temp;

	if (!arena || !*arena)
		return (-1);
	temp = *arena;
	free(temp->data);
	free(temp);
	temp = NULL;
	return (1);
}

int	ft_arena_list_free(t_arena **arena)
{
	t_arena	*current;
	t_arena	*next;

	if (!arena)
		return (-1);
	if (!*arena)
		return (1);
	current = *arena;
	next = current->next;
	while (current)
	{
		next = current->next;
		if (ft_arena_free(&current) < 0)
			return (-1);
		current = next;
	}
	*arena = NULL;
	return (1);
}
