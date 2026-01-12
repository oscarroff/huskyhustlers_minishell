/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:34:30 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/05 11:34:30 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

static int run_external(t_exec *exec);

//TODO: see if return values need to be caught for some loop behavior, like cleanup / breaks, or not.
// (in either case error status code is already saved in exec->exec_status)

int	run(t_exec *execution, int in)
{
	//TODO: sub-process signal handlers
	set_in_out(execution, in);
	if (execution->builtin)
	{
		run_builtin(execution);
		clean_exit(execution->tree, NULL);
		return (ERROR);
	}
	else
	{
		return (run_external(execution));
	}
}

int run_builtin(t_exec *exec)
{
	static t_func	*dispatch_table[8] = \
	{
		NULL,
		&echo,
		&cd,
		&pwd,
		&export,
		&unset,
		&env,
		&b_exit
	};

	return (dispatch_table[exec->builtin](exec));
}

static int run_external(t_exec *exec)
{
	char	*cmd;
	char	**args;
	char	**envp;

	envp = NULL;
	cmd = exec->extern_cmd_path;
	args = exec->cmd->argv;
	envp_export(&envp, exec->tree);
	execve(cmd, args, envp);
	return (ERROR);
}