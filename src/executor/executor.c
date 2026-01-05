/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:24:34 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/04 16:41:31 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

		// Just remember that the vec_get needs to be cast to the type. So for
		// the command table that's t_cmd. For envp (environmental parameters)
		// that will be char e.g. *(char **). Tho I haven't built that yet. :D

//SAVE EXIT_STATUS IN STRUCT, 
//RETURN BACK TO PROMPT LOOP WITH ONE GEN ERRORMSG VIA ERROR_HANDLING FUNCTION
//ERROR HANDLING COULD TAKE EXEC TO READ THE PRECISE problem AND HANDLE ACCORDINGLY.

static void init_execution(t_exec *execution, t_vec *cmd_tab, size_t i);
static void	execute_cmd(t_exec *execution, int in);

void	executor(t_tree *tree, t_flag mode_flag)
{
	pid_t		*pids;
	t_exec		execution;
	t_vec		*command_table;
	int			in;
	size_t		i;

	command_table = tree->cmd_tab;

	//FIX: this seems to give a very screwed up pids array.
	ft_arena_alloc(tree->a_buf, (void **)&pids, sizeof(pid_t) * command_table->len + 1);
	ft_memset(pids, 0, command_table->len);

	in = STDIN_FILENO;
	execution.tree = tree;
	i = 0;
	while (i < command_table->len)
	{
		if (tree->mode == FLAG_DEBUG)
		{
			printf("len of cmd table: %zu\n", command_table->len);
		}

		init_execution(&execution, command_table, i);
		
		if (tree->mode == FLAG_DEBUG)
		{
			size_t		j;
			j = 0;
			while (j < execution.cmd->argc)
			{
				ft_printf("arg is: %s\n", execution.cmd->argv[j]);
				j++;
			}
		}


//TODO: test PID tracking and create wait_processes function.

		execute_cmd(&execution, in);
		pids[i] = execution.pid;
		if (in != STDIN_FILENO)
			close(in);
		close_node_fds(&execution);
		if (execution.next_exists)
		{
			close(execution.pipefd[1]);
			in = execution.pipefd[0];
		}
		i++;

		if (tree->mode == FLAG_DEBUG)
		{
			ft_printf("input is: %s\n", execution.cmd->input);
			ft_printf("output is: %s\n", execution.cmd->output);
		}
	}

	if (pids[0] > 0)
		wait_processes(&execution, pids);
	tree->exit_code = execution.exec_status;
	// mode_flag has the value FLAG_DEBUG when executing with '-debug' from
	// the terminal i.e. ./minishell -debug, useful for debugging later
	(void)mode_flag;
}

//TODO: general status from execute_cmd(), run() or run_builtin() not caught yet.
static void	execute_cmd(t_exec *execution, int in)
{
	if (execution->tree->mode == FLAG_DEBUG)
		printf("in execute_cmd?\n");
	if (verify_cmd(execution))
	{
		set_env_defaults(execution->tree);
		return ;
	}
	set_env_defaults(execution->tree);
	if (execution->next_exists)
	{
		get_pipe(execution);
		set_fork(execution);
		if (execution->pid == 0)
			run(execution, in);
	}
	else if (!execution->builtin)
	{
		set_fork(execution);
		if (execution->pid == 0)
			run(execution, in);
	}
	else
	{
		set_redirs(execution);
		run_builtin(execution);
	}
}

void	set_env_defaults(t_tree *tree)
{
	(void) tree;
	//to be seen what is left
}

static void init_execution(t_exec *execution, t_vec *cmd_tab, size_t i)
{
	t_cmd		*command;

	command = *(t_cmd **)vec_get(cmd_tab, i);
	execution->cmd = command;
	execution->extern_cmd_path = NULL;
	execution->redir_in = STDIN_FILENO;
	execution->redir_out = STDOUT_FILENO;
	execution->exec_status = 0;
	execution->builtin = FALSE;
	if (i + 1 < cmd_tab->len)
		execution->next_exists = true;
	else
		execution->next_exists = false;
	execution->pid = -1;
}
