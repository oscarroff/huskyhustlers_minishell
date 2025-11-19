/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:53:33 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/19 22:05:24 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static void	set_cmd(t_cmd *cmd, t_cmdv vars);

void	init_cmd_table(t_tree *tree, t_cmdv *vars)
{
	if (!vec_alloc(&tree->cmd_tab, tree->arena))
		return (clean_exit(tree, MSG_MALLOCF));
	if (!vec_new(tree->cmd_tab, 0, sizeof(t_cmd *)))
		clean_exit(tree, MSG_MALLOCF);
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
	if (vars.argc > 0)
		if (!ft_arena_alloc(tree->arena, (void **)&new->argv,
				(vars.argc + 1) * sizeof(char *)))
			clean_exit(tree, MSG_MALLOCF);
	if (vars.inputc > 0)
		if (!ft_arena_alloc(tree->arena, (void **)&new->input,
				(vars.inputc + 1) * sizeof(char *)))
			clean_exit(tree, MSG_MALLOCF);
	if (vars.outputc > 0)
		if (!ft_arena_alloc(tree->arena, (void **)&new->output,
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
	if (vars.argc > 0)
		cmd->argv[0] = NULL;
	else
		cmd->argv = NULL;
	if (vars.inputc > 0)
		cmd->input[0] = NULL;
	else
		cmd->input = NULL;
	if (vars.outputc > 0)
		cmd->output[0] = NULL;
	else
		cmd->output = NULL;
}

void	get_cmd_vars(t_cmdv *vars, t_vec *tokens, size_t i)
{
	t_token	*tok;

	while (i < tokens->len)
	{
		tok = *(t_token **)vec_get(tokens, i);
		if (tok->type == TOK_PIPE)
			break ;
		if (tok->type == TOK_WORD || tok->type == TOK_QUOTATION)
			vars->argc += 1;
		if (tok->type == TOK_IO && tok->redirect == RDR_READ)
			vars->inputc += 1;
		if (tok->type == TOK_IO
			&& (tok->redirect == RDR_WRITE || tok->redirect == RDR_APPEND))
			vars->outputc += 1;
		vars->len += 1;
		i++;
	}
}
