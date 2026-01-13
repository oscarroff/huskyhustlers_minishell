/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:34:27 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/05 11:34:27 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"
#include <sys/wait.h>

void	get_pipe(t_exec *exec)
{
	if (pipe(exec->pipefd) == ERROR)
		exe_err(exec, M_SYS, (int []){FATAL, EXIT_FAILURE});
}

void	set_in_out(t_exec *exec, int in)
{
	if (in != STDIN_FILENO)
	{
		if (dup2(in, STDIN_FILENO) == ERROR)
			exe_err(exec, M_SYS, (int []){FATAL, EXIT_FAILURE});
		close(in);
	}
	if (exec->next_exists)
	{
		close(exec->pipefd[0]);
		if (dup2(exec->pipefd[1], STDOUT_FILENO) == ERROR)
			exe_err(exec, M_SYS, (int []){FATAL, EXIT_FAILURE});
		close(exec->pipefd[1]);
	}
	set_redirs(exec);
	if (exec->redir_in == ERROR || exec->redir_out == ERROR)
	{
		exe_err(exec, M_SYS, (int []){FATAL, EXIT_FAILURE});
	}
}

void	set_fork(t_exec *exec)
{
	exec->pid = fork();
	if (exec->pid == -1)
		exe_err(exec, M_SYS, (int []){FATAL, EXIT_FAILURE});
}

void	set_redirs(t_exec *exec)
{
	if (exec->redir_in != STDIN_FILENO && exec->redir_in != ERROR)
	{
		if (dup2(exec->redir_in, STDIN_FILENO) == ERROR)
			exe_err(exec, M_SYS, (int []){FATAL, EXIT_FAILURE});
		close(exec->redir_in);
	}
	if (exec->redir_out != STDOUT_FILENO && exec->redir_out != ERROR)
	{
		if (dup2(exec->redir_out, STDOUT_FILENO) == ERROR)
			exe_err(exec, M_SYS, (int []){FATAL, EXIT_FAILURE});
		close(exec->redir_out);
	}
}

void wait_processes(t_exec *exec, pid_t *pids)
{
	int		status;
	size_t	i;

	i = 0;
	while (pids[i] > 0)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			if (WIFEXITED(status) && !pids[i + 1])
				exec->exec_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status) && !pids[i + 1])
				exec->exec_status = 128 + WTERMSIG(status);
		}
		if ((exec->redir_in == ERROR || exec->redir_out == ERROR) \
				&& !pids[i + 1])
			exec->exec_status = ERR_GEN;
		i++;
	}
}
