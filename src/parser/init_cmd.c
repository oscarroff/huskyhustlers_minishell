/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:53:33 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 16:42:21 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static void	set_cmd(t_cmd *cmd, t_cmdv vars);
static void null_array(char **array, size_t len);

void	init_cmd_table(t_tree *tree, t_cmdv *vars)
{
	if (!vec_alloc(&tree->cmd_tab, tree->arena))
		return (clean_exit(tree, MSG_MALLOCF));
	if (!vec_new(tree->cmd_tab, 0, sizeof(t_cmd *)))
		clean_exit(tree, MSG_MALLOCF);
	vars->i = 0;
	vars->len = 0;
	vars->argc = 0;
	vars->inputc = 0;
	vars->outputc = 0;
}

void	init_cmd(t_cmd **cmd, t_cmdv vars, t_tree *tree)
{
	t_cmd	*new;

	new = NULL;
	if (!ft_arena_alloc(tree->arena, (void **)&new, sizeof(t_cmd)))
		clean_exit(tree, MSG_MALLOCF);
	if (!ft_arena_alloc(tree->arena, (void **)&new->argv,
			(vars.argc + 1) * sizeof(char *))
		|| !ft_arena_alloc(tree->arena, (void **)&new->input,
			(vars.inputc + 1) * sizeof(char *))
		|| !ft_arena_alloc(tree->arena, (void **)&new->output,
			(vars.outputc + 1) * sizeof(char *)))
		clean_exit(tree, MSG_MALLOCF);
	set_cmd(new, vars);
	*cmd = new;
	if (!vec_push(tree->cmd_tab, cmd))
		clean_exit(tree, MSG_MALLOCF);

}

static void	set_cmd(t_cmd *cmd, t_cmdv vars)
{
	cmd->argc = vars.argc;
	cmd->argv = NULL;
	null_array(cmd->input, vars.inputc);
	null_array(cmd->output, vars.outputc);
	cmd->heredoc = NULL;
}

static void null_array(char **array, size_t len)
{
	while (len > 0)
		array[len--] = NULL;
}
