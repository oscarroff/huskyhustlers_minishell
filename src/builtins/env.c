/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:27:53 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/15 16:25:33 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"
#include "../../inc/minishell.h"

static void	print_env(t_exec *exec, char *env);
static bool	is_initialized(const char *var);

int	env(t_exec *exec)
{
	char	*arg;
	char	**envp;
	size_t	i;

	if (!exec)
		return (ERROR);
	arg = exec->cmd->argv[1];
	if (arg)
	{
		exec->exec_status = exe_err(exec, ft_strjoin(": ", arg), (int []){WARN,
				ERR_CMDNF});
		return (ERROR);
	}
	envp = NULL;
	if (!envp_export(&envp, exec->tree))
		return (ERROR);
	i = 0;
	while (envp[i])
	{
		if (is_initialized(envp[i]))
			print_env(exec, envp[i]);
		i++;
	}
	return (0);
}

static void	print_env(t_exec *exec, char *env)
{
	int	fd_out;

	fd_out = STDOUT_FILENO;
	if (exec->redir_out > 0)
		fd_out = exec->redir_out;
	try_write_endl(exec->tree, fd_out, env);
}

static bool	is_initialized(const char *var)
{
	size_t	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (true);
		i++;
	}
	return (false);
}
