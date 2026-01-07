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
		if (errno == ENOENT) //FIX: add checking saved cwd to ascertain it is saved before access.
			//ft_putendl_fd(exec->cwd, fd_out);  //FIX: current working dir gotta always be saved somewhere.
			return (0);
		else
			{;}
			//clean_exit(exec->tree, "getcwd failed");	OUTDATED. REPLACED OR GONE?
	}
	ft_putendl_fd(pwd, fd_out);
	return (0);
}