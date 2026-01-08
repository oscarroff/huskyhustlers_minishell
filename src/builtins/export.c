/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:27:57 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/05 11:27:58 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

static int	display(t_exec *exec);
static int	put_var(t_exec *exec);

int export(t_exec *exec)
{
	if (!exec->cmd->argv[1])
		return (display(exec));
	else
		return (put_var(exec));
}

static int	display(t_exec *exec)
{
	int		fd_out;

	fd_out = STDOUT_FILENO;
	if (exec->redir_out)
		fd_out = exec->redir_out;
	//need envp_export for getting a char **env for quicksort.
	return (0);
}

static int	put_var(t_exec *exec)
{
	size_t		i;
	char		**args;

	i = 1;
	args = exec->cmd->argv;
	while (args[i])
	{
		if (envp_set(exec->tree, exec->cmd->argv[i]))
			clean_exit(exec->tree, NULL);
		i++;
	}
	return (0);
}