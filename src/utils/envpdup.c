/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:39:44 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/17 21:40:53 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include "../../inc/minishell.h"

static int	envpduphelper(char **dst, const char *src, t_arena *arena)
{
	char	*new;
	size_t	len;

	new = NULL;
	if (!dst || !arena)
		return (FAIL);
	if (!src)
		return (SUCCESS);
	len = ft_strlen(src);
	if (!ft_arena_alloc(arena, (void **)&new, (len + 1) * sizeof(char)))
		return (FAIL);
	ft_memcpy(new, src, len);
	new[len] = '\0';
	*dst = new;
	return (SUCCESS);
}

int	envpdup(char ***dst, t_vec *envp, t_arena *arena)
{
	char	**new;
	size_t	i;

	new = NULL;
	i = 0;
	if (!dst || !arena)
		return (FAIL);
	if (!envp || envp->len == 0)
		return (SUCCESS);
	if (!ft_arena_alloc(arena, (void **)&new, (envp->len + 1) * sizeof(char *)))
		return (FAIL);
	while (i < envp->len)
	{
		new[i] = NULL;
		if (!envpduphelper(&new[i], *(const char **)vec_get(envp, i), arena))
			return (FAIL);
		i++;
	}
	new[i] = NULL;
	*dst = new;
	return (SUCCESS);
}
