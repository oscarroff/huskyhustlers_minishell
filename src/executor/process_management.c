#include "../../inc/minishell.h"
#include "../../inc/execution.h"

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

void	set_redirs(t_exec *exec) // ATM redir_in AND out IN EXEC ARE DEFAULTED TO STD FILENO
{
	get_redirs(exec); //get actual redir data from tommie struct! input and output in tree.
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

void wait_processes(t_exec execution)
{
	(void) execution;
	//waitpids();
}
