/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superstrndup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:05:52 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/17 23:13:10 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_superstrndup(char **dst, const char *src, size_t len, t_arena *a)
{
	char	*new;

	if (!dst)
		return (FAIL);
	if (!src)
	{
		*dst = NULL;
		return (SUCCESS);
	}
	new = NULL;
	if (a)
		if (!ft_arena_alloc(a, (void **)&new, (len + 1) * sizeof(char)))
			return (FAIL);
	if (!a)
	{
		new = malloc((len + 1) * sizeof(char));
		if (!new)
			return (FAIL);
	}
	if (len > 0)
		ft_memcpy(new, src, len);
	new[len] = '\0';
	*dst = new;
	return (SUCCESS);
}
