/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:24:34 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/07 17:06:22 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"
#include "../../inc/parsing.h"

		// Just remember that the vec_get needs to be cast to the type. So for
		// the command table that's t_cmd. For envp (environmental parameters)
		// that will be char e.g. *(char **). Tho I haven't built that yet. :D

static void init_exec(t_exec *exec, t_tree *tree, t_vec *cmd_tab, size_t i);
static int	execute_cmd(t_exec *execution, int in);
static void	handle_fildes(t_exec *exec, int *in);
static void	set_env_defaults(t_exec *exec);

void	executor(t_tree *tree)
{
	pid_t		*pids;
	t_exec		execution;
	t_vec		*cmd_tab;
	int			in;
	size_t		i;

	cmd_tab = tree->cmd_tab;
	if (!ft_arena_alloc(tree->a_buf, (void **)&pids, sizeof(pid_t) * (cmd_tab->len + 1)))
		return (try_write_endl(tree, 2, "Arena alloc fail"));
	ft_memset(pids, 0, (1 + cmd_tab->len) * sizeof(pid_t));
	in = STDIN_FILENO;
	i = 0;
	while (i < cmd_tab->len)
	{
		init_exec(&execution, tree, cmd_tab, i);
		get_redirs(&execution);
		execute_cmd(&execution, in);
		pids[i] = execution.pid;
		handle_fildes(&execution, &in);
		i++;
	}
	if (pids[0] > 0)
		wait_processes(&execution, pids);
	tree->exit_code = execution.exec_status;
}

static int	execute_cmd(t_exec *execution, int in)
{
	if (verify_cmd(execution))
	{
		set_env_defaults(execution);
		return (ERROR);
	}
	set_env_defaults(execution);
	if (execution->next_exists || execution->prev_exists || !execution->builtin)
	{
		if (execution->next_exists)
			get_pipe(execution);
		set_fork(execution);
		if (execution->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			run(execution, in);
		}
	}
	else
	{
		set_redirs(execution);
		run_builtin(execution);
	}
	return (0);
}

static void	handle_fildes(t_exec *exec, int *in)
{
	if (*in != STDIN_FILENO)
		close(*in);
	close_node_fds(exec);
	if (exec->next_exists)
	{
		close(exec->pipefd[1]);
		*in = exec->pipefd[0];
	}
}

static void init_exec(t_exec *exec, t_tree *tree, t_vec *cmd_tab, size_t i)
{
	t_cmd		*command;

	exec->tree = tree;
	command = *(t_cmd **)vec_get(cmd_tab, i);
	exec->cmd = command;
	exec->extern_cmd_path = NULL;
	exec->redir_in = STDIN_FILENO;
	exec->redir_out = STDOUT_FILENO;
	exec->exec_status = 0;
	exec->builtin = FALSE;
	if (i + 1 < cmd_tab->len)
		exec->next_exists = true;
	else
		exec->next_exists = false;
	exec->pid = -1;
	if (i > 0)
		exec->prev_exists = true;
	else
		exec->prev_exists = false;
}

static void	set_env_defaults(t_exec *exec)
{
	char	*last_arg;
	char	**argv;
	int		i;

	i = 0;
	argv = exec->cmd->argv;
	while(argv[i])
		i++;
	last_arg = argv[i - 1];
	envp_insert(exec->tree, "_", 1, last_arg);
}
