/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:53:33 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 11:15:33 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static void	set_cmd(t_cmd *cmd, size_t argc);

void	init_cmd(t_cmd **cmd, size_t argc, t_tree *tree)
{
	t_cmd	*new;

	new = NULL;
	if (!ft_arena_alloc(tree->arena, (void **)&new, sizeof(t_cmd)))
		clean_exit(tree, MSG_MALLOCF);
	set_cmd(new, argc);
	if (!ft_arena_alloc(tree->arena, (void **)&new->argv,
		(argc + 1) * sizeof(char *)))
		clean_exit(tree, MSG_MALLOCF);
	// if (!vec_alloc(&new->envp, tree->arena))
	// 	clean_exit(tree, MSG_MALLOCF);
	*cmd = new;
	if (!vec_push(tree->cmd_tab, cmd))
		clean_exit(tree, MSG_MALLOCF);
}

static void	set_cmd(t_cmd *cmd, size_t argc)
{
	cmd->argc = argc;
	cmd->argv = NULL;
	// cmd->envp = NULL;
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->heredoc = NULL;
}
