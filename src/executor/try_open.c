/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:58:57 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/16 13:59:04 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

int	try_open(t_exec *exec, char *f, int o_flag, int p_flag)
{
	int	fd;

	fd = open(f, o_flag, p_flag);
	if (fd == -1)
	{
		if (errno == EACCES)
			exec->exec_status = exe_err(exec, NULL, (int []){WARN, ERR_GEN});
		else
		{
			if (exec->tree)
				clean_exit(exec->tree, MSG_SYSCALL);
		}
	}
	return (fd);
}
