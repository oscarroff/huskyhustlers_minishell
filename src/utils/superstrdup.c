/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superstrdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:05:52 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/17 21:58:36 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_superstrdup(char **dst, const char *src, t_arena *arena)
{
	char	*new;
	size_t	len;

	if (!dst || !arena)
		return (FAIL);
	if (!src)
		return (SUCCESS);
	new = NULL;
	len = ft_strlen(src);
	if (arena)
		if (!ft_arena_alloc(arena, (void **)&new, (len + 1) * sizeof(char)))
			return (FAIL);
	if (!arena)
	{
		new = malloc((len + 1) * sizeof(char));
		if (!new)
			return (FAIL);
	}
	ft_memcpy(new, src, len);
	new[len] = '\0';
	*dst = new;
	return (SUCCESS);
}
