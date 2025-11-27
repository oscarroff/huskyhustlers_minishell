/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isambiguous.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:57:33 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 19:35:51 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isambiguous(char const *s)
{
	size_t	space_flag;

	space_flag = 0;
	while (*s)
	{
		if (space_flag == 1 && !ft_isspace(*s))
			return (true);
		if (ft_isspace(*s))
			space_flag = 1;
		s++;
	}
	return (false);
}
