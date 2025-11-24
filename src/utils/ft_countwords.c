/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:57:33 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 18:10:03 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_countwords(char const *s, char c)
{
	size_t	wcount;

	wcount = 0;
	while (*s)
	{
		if (*s != c && *s)
		{
			wcount++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (wcount);
}
