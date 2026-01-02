/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:24:34 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/02 17:18:07 by jvalkama         ###   ########.fr       */
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

static void set_execution(t_exec *execution, t_vec *cmd_tab, t_tree *tree, size_t i);

void	executor(t_tree *tree, t_flag mode_flag)
{
	t_exec		execution;
	t_vec		*command_table;
	int			in;
	size_t		i;

	in = STDOUT_FILENO;
	execution.tree = tree;
	command_table = tree->cmd_tab;
	i = 0;
	while (i < command_table->len)
	{
		set_execution(&execution, command_table, tree, i);

		
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


			
		if (verify_cmd(&execution))
			break ;
		if (execution.next_exists)
		{
			get_pipe(&execution);
			set_fork(&execution);
			//set_redirs();
		}
		else if (!execution.builtin)
		{
			set_fork(&execution);
		}
		set_in_out(&execution);
		run(&execution);
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
	//if (execution.pids)
	//	wait(execution);
	tree->exit_code = execution.exec_status;
	// mode_flag has the value FLAG_DEBUG when executing with '-debug' from
	// the terminal i.e. ./minishell -debug, useful for debugging later
	(void)mode_flag;
}



void wait(t_exec execution)
{
	(void) execution;
	//waitpids();
}

static void set_execution(t_exec *execution, t_vec *cmd_tab, t_tree *tree, size_t i)
{
	t_cmd	*command;

	command = *(t_cmd **)vec_get(cmd_tab, i);
	execution->cmd = command;
	execution->redir_in = STDIN_FILENO;
	execution->redir_out = STDOUT_FILENO;
	execution->exec_status = 0;
	execution->builtin = FALSE;
	execution->cmd = NULL;
	if (i + 1 < tree->cmd_tab->len)
		execution->next_exists = true;
	else
		execution->next_exists = false;
	execution->pid = -1;
}
