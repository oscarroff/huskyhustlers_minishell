/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:28:00 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/05 11:28:01 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

int pwd(t_exec *exec)
{
	char	*pwd;
	char	buf[PATH_MAX];
	int		fd_out;

	fd_out = STDOUT_FILENO;
	pwd = getcwd(buf, sizeof(buf));
	if (!pwd)
	{
		exec->exec_status = ERR_GEN;
		if (errno == ENOENT)
		{
			exec->exec_status = exe_err(exec, M_GETOUT, (int []){WARN, 0});
			return (0);
		}
		else
			exe_err(exec, M_SYS, (int []){FATAL, EXIT_FAILURE});
	}
	ft_putendl_fd(pwd, fd_out);
	return (0);
}