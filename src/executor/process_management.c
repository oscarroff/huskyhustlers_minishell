#include "../../inc/minishell.h"
#include "../../inc/execution.h"

void	get_pipe(t_exec *exec)
{
	if (pipe(exec->pipefd) == ERROR)
		exe_err(exec, M_SYS, (int []){FATAL, EXIT_FAILURE});
}

void	set_in_out(t_exec *exec)
{
	(void) exec;
}

void	set_fork(t_exec *exec)
{
	exec->pid = fork();
	if (exec->pid == -1)
		exe_err(exec, M_SYS, (int []){FATAL, EXIT_FAILURE});
}

void	set_redirs(t_exec *exec)
{
	(void) exec;
}
