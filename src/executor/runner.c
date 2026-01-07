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
	//TODO: sub-process signal handlers
	set_in_out(execution, in);
	if (execution->builtin)
	{
		return (run_builtin(execution));
		clean_exit(execution->tree, NULL);
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
	printf("failed external: cmd: %s args[0]: %s args[1]: %s\n", cmd, args[0], args[1]);
	perror("error");

	int i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	printf("%s\n", envp[i]);
	return (ERROR);
}