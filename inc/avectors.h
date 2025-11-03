/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avectors.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:12:42 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/03 12:10:38 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVECTORS_H
# define AVECTORS_H

# include "minishell.h"

typedef struct s_avec
{
	void	**data;
	size_t	elem_size;
	size_t	alloc_size;
	size_t	len;
	t_arena	*arena;
}	t_avec;

// VECTORS
void	avec_init(t_avec *dst, size_t init_len, t_arena *arena);
int		avec_new(t_avec *dst, size_t init_len, t_arena *arena);
void	avec_free(t_avec *src);
int		avec_from(t_avec *dst, void *src, t_arena *arena);
int		avec_copy(t_avec *dst, t_avec *src);
void	avec_printf(const t_avec *src, char printf_flag);
int		avec_resize(t_avec *src, size_t target_len);
int		avec_push(t_avec *dst, void *src);
int		avec_pop(void *dst, t_avec *src);
void	*avec_get(t_avec *src, size_t index);
int		avec_insert(t_avec *dst, void *src, size_t index);
int		avec_remove(t_avec *src, size_t index);
int		avec_append(t_avec *dst, t_avec *src);
int		avec_prepend(t_avec *dst, t_avec *src);
int		avec_inpend(t_avec *dst, t_avec *src, size_t after);
int		avec_iter(t_avec *src, void (*f)(void *));
int		avec_map(t_avec *dst, t_avec *src, void (*f)(void *));
int		avec_filter(t_avec *dst, t_avec *src, bool (*f)(void *));
int		avec_reduce(void *acc, t_avec *src, void (*f)(void *, void *));
int		avec_sort(t_avec *src, int (*f)(void *, void *));

#endif
