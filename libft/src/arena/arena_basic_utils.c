/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_basic_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:29:36 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/07 14:24:35 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_arena_init(t_arena **arena, size_t capacity)
{
	t_arena	*new;

	if (!arena || capacity == 0)
		return (ft_errno_set(EINVAL, KO));
	if (capacity > (SIZE_MAX / sizeof(uint8_t)))
		return (ft_errno_set(ERANGE, KO));
	new = malloc(sizeof(t_arena));
	if (!new)
		return (ft_errno_set(ENOMEM, KO));
	new->data = malloc(sizeof(uint8_t) * capacity);
	if (!new->data)
	{
		free(new);
		return (ft_errno_set(ENOMEM, KO));
	}
	new->capacity = capacity;
	new->size = 0;
	new->next = NULL;
	*arena = new;
	return (OK);
}

int	ft_arena_alloc(t_arena *arena, void **ptr, size_t size)
{
	t_arena	*current;
	t_arena	*next;
	size_t	capacity;

	if (!arena || !arena->data || size == 0)
		return (ft_errno_set(EINVAL, KO));
	current = arena;
	capacity = size;
	next = NULL;
	while (current->size + size >= current->capacity && current->next)
		current = current->next;
	if (current->size + size > current->capacity)
	{
		current->size = current->capacity;
		if (capacity < ARENA_BUF)
			capacity = ARENA_BUF;
		if (ft_arena_init(&next, capacity) < 0)
			return (KO);
		current->next = next;
		current = current->next;
	}
	*ptr = (void *)&current->data[current->size];
	current->size += size;
	return (OK);
}

int	ft_arena_reset(t_arena *arena)
{
	if (!arena)
		return (ft_errno_set(EINVAL, KO));
	arena->size = 0;
	return (OK);
}

int	ft_arena_free(t_arena **arena)
{
	t_arena	*temp;

	if (!arena || !*arena)
		return (ft_errno_set(EINVAL, KO));
	temp = *arena;
	free(temp->data);
	temp->data = NULL;
	free(temp);
	*arena = NULL;
	return (OK);
}

int	ft_arena_list_free(t_arena **arena)
{
	t_arena	*current;
	t_arena	*next;

	if (!arena)
		return (ft_errno_set(EINVAL, KO));
	if (!*arena)
		return (OK);
	current = *arena;
	while (current)
	{
		next = current->next;
		if (ft_arena_free(&current) < 0)
			return (KO);
		current = next;
	}
	*arena = NULL;
	return (OK);
}
