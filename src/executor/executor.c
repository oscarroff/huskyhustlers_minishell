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

#include "minishell.h"
#include "execution.h"

// Example fetching of data from structs and vectors
void	executor(t_tree *tree, t_flag mode_flag)
{
	t_vec	*command_table;
	t_cmd	*command;
	size_t	i;
	size_t	j;

	// Casting pointer, but you could just work with tree->cmd_tab
	command_table = tree->cmd_tab;
	i = 0;
	while (i < command_table->len)
	{
		// This is the most confusing bit for me, the dbl pointer *(t_cmd **)
		// Just remember that the vec_get needs to be cast to the type. So for
		// the command table that's t_cmd. For envp (environmental parameters)
		// that will be char e.g. *(char **). Tho I haven't built that yet. :D
		command = *(t_cmd **)vec_get(command_table, i);
		j = 0;
		while (j < command->argc)
		{
			ft_printf("arg is: %s\n", command->argv[j]);
			j++;
		}
		i++;
		ft_printf("input is: %s\n", command->input);
		ft_printf("output is: %s\n", command->output);
	}
	// mode_flag has the value FLAG_DEBUG when executing with '-debug' from
	// the terminal i.e. ./minishell -debug, useful for debugging later
	(void)mode_flag;
}
