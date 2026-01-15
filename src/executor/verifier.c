/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifier.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:34:33 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/15 16:56:30 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static bool			is_cmd(t_exec *exec);
static t_builtin	is_builtin(char *cmd_name, t_exec *exec);
static bool			is_external(char *cmd_name, t_exec *exec);

int	verify_cmd(t_exec *exec)
{
	if (exec->cmd)
	{
		if (is_cmd(exec))
			return (exec->exec_status);
	}
	exec->exec_status = exe_err(exec, M_CMDNF, (int []){WARN, ERR_CMDNF});
	return (ERROR);
}

static bool	is_cmd(t_exec *exec)
{
	char	*cmd_name;

	if (exec->cmd->argv == NULL)
		return (false);
	cmd_name = exec->cmd->argv[0];
	if (is_builtin(cmd_name, exec))
	{
		return (true);
	}
	if (is_external(cmd_name, exec))
	{
		if (access(exec->extern_cmd_path, X_OK) == ERROR)
			exec->exec_status = exe_err(exec, M_FEXE, \
(int []){WARN, ERR_CEXEC});
		return (true);
	}
	return (false);
}

static t_builtin	is_builtin(char *cmd_name, t_exec *exec)
{
	t_builtin	select;
	static char	*options[] = {NULL, "echo", "cd", "pwd", "export", "unset", \
"env", "exit"};

	select = 7;
	while (select > 0)
	{
		if (ft_strcmp(options[select], cmd_name) == 0)
			break ;
		select--;
	}
	exec->builtin = select;
	return (select);
}

static inline bool	is_relative_path(t_exec *exec, char *cmd_name)
{
	if (access(cmd_name, F_OK) == 0)
	{
		exec->extern_cmd_path = cmd_name;
		return (true);
	}
	return (false);
}

static bool	is_external(char *cmd_name, t_exec *exec)
{
	char	*path_variable;

	path_variable = envp_get("PATH", exec->tree);
	if (!path_variable || cmd_name[0] == '/' || cmd_name[0] == '.')
	{
		return (is_relative_path(exec, cmd_name));
	}
	else
	{
		return (is_on_path_var(exec, cmd_name, path_variable));
	}
}
