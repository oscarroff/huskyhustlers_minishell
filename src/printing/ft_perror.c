/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:47:54 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/07 11:47:29 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_error(char *s)
{
	if (s)
	{
		// TODO: Does this need try_write() protection? We're already failing!
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (FAIL);
}
