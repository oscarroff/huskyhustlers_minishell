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

int run(t_exec *execution, int in)
{
	//signal handlers
	set_in_out(execution, in);
	if (execution->builtin)
	{
		return (run_builtin(execution));
		//clean_exit();		FORKED BUILTINS ALWAYS EXIT
	}
	else
		return (run_external(execution));
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

	cmd = exec->cmd->argv[0];
	args = exec->cmd->argv;
	envp = (char **)vec_get(exec->tree->envp, 0);
	execve(cmd, args, envp);
	return (ERROR);
}