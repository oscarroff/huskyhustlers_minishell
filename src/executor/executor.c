/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:24:34 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 17:45:31 by thblack-         ###   ########.fr       */
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

static void set_execution(t_exec *execution, t_tree *tree);

void	executor(t_tree *tree, t_flag mode_flag)
{
	t_exec	execution;
	t_cmd	*command;
	t_vec	*command_table;
	size_t	i;
	size_t	j;

	execution.tree = tree;
	command_table = tree->cmd_tab;
	i = 0;
	while (i < command_table->len)
	{
		command = *(t_cmd **)vec_get(command_table, i);
		set_execution(&execution, tree);


			j = 0;
			while (j < command->argc)
			{
				ft_printf("arg is: %s\n", command->argv[j]);
				j++;
			}


		{
			execution.cmd = command;
			verify_cmd(&execution);
			if (execution.next_exists)
			{
				get_pipe();
				set_in_out();
				set_fork(); //FIX: forking here may cause issues with builtins.
			}
			run(&execution);
		}

		i++;
		ft_printf("input is: %s\n", command->input);
		ft_printf("output is: %s\n", command->output);
		
	}
	if (execution.pids)
		wait(execution);
	// mode_flag has the value FLAG_DEBUG when executing with '-debug' from
	// the terminal i.e. ./minishell -debug, useful for debugging later
	(void)mode_flag;
}

static void set_execution(t_exec *execution, t_tree *tree)
{
	(void) tree;
	execution->exec_status = 0;
	execution->builtin = FALSE;
	execution->cmd = NULL;
	execution->next_exists = false;
	execution->pids = NULL;
}

void wait(t_exec execution)
{
	(void) execution;
}
