/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:01:27 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/15 16:03:14 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_flags(t_flag *mode_flag, int argc, char **argv)
{
	int		i;
	t_flag	tmp;

	if (argc == 1)
		return (SUCCESS);
	i = 1;
	while (i < argc)
	{
		tmp = FLAG_DEFAULT;
		if (ft_strcmp(argv[i], "-debug") && ft_strcmp(argv[i], "-envp")
			&& ft_strcmp(argv[i], "-d") && ft_strcmp(argv[i], "-e"))
		{
			ft_putendl_fd(MSG_FLAGPMT, 2);
			return (FAIL);
		}
		if (!ft_strcmp(argv[i], "-debug") || !ft_strcmp(argv[i], "-d"))
			tmp = FLAG_DEBUG;
		else if (!ft_strcmp(argv[i], "-envp") || !ft_strcmp(argv[i], "-e"))
			tmp = FLAG_ENVP;
		if (tmp == *mode_flag)
			return (FAIL);
		*mode_flag += tmp;
		i++;
	}
	return (SUCCESS);
}
