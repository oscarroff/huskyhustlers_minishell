/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:03:45 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 16:41:18 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static void	get_cmd_vars(t_cmdv *vars, t_vec *tokens, size_t i);
static void	parse_tokens(t_cmd *cmd, t_vec *tokens, size_t i, t_tree *tree);
static void	parse_argv(t_cmd *cmd, t_token *tok, size_t argi, t_tree *tree);
static void	parse_io(t_cmd *cmd, t_token *tok, t_tree *tree);

void	commandise(t_tree *tree, t_vec *tokens)
{
	t_cmd	*cmd;
	t_cmdv	vars;
	size_t	i;

	if (!tree || !tokens)
		return ;
	if (!tree->cmd_tab)
		init_cmd_table(tree, &vars);
	i = 0;
	while (vars.i < tokens->len)
	{
		cmd = NULL;
		get_cmd_vars(&vars, tokens, i);
		init_cmd(&cmd, vars, tree);
		parse_tokens(cmd, tokens, i, tree);
		i += vars.len;
		if (i < tokens->len)
			i++;
	}
}

static void	get_cmd_vars(t_cmdv *vars, t_vec *tokens, size_t i)
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

static void	parse_tokens(t_cmd *cmd, t_vec *tokens, size_t i, t_tree *tree)
{
	t_token	*tok;
	size_t	argi;

	argi = 0;
	while (i < tokens->len)
	{
		tok = *(t_token **)vec_get(tokens, i);
		if (tok->type == TOK_PIPE)
			break ;
		else if (tok->type == TOK_IO)
			parse_io(cmd, tok, tree);
		else if (tok->type == TOK_WORD || tok->type == TOK_QUOTATION)
			parse_argv(cmd, tok, argi++, tree);
		i++;
	}
	cmd->argv[cmd->argc] = NULL;
}

static void	parse_argv(t_cmd *cmd, t_token *tok, size_t argi, t_tree *tree)
{
	char	*arg;
	void	*src;
	size_t	len;

	src = tok->tok_chars->data;
	len = tok->tok_chars->len;
	arg = NULL;
	if (!ft_arena_alloc(tree->arena, (void **)&arg, (len + 1) * sizeof(char)))
		clean_exit(tree, MSG_MALLOCF);
	ft_memcpy(arg, src, len * sizeof(char));
	arg[len] = '\0';
	ft_printf("argi: %u\n", (uint32_t)argi);
	ft_printf("ptr %p\n", cmd->argv[argi]);
	ft_printf("str %s\n", arg);
	cmd->argv[argi] = arg;
}

static void	copy_str(char **str, void *ptr, size_t len, t_tree *tree)
{
	char	*new;

	new = NULL;
	if (!ft_arena_alloc(tree->arena, (void **)&new, (len + 1) * sizeof(char)))
		clean_exit(tree, MSG_MALLOCF);
	ft_memcpy(new, ptr, len);
	new[len] = '\0';
	*str = new;
}

static void	copy_redirect(char **array, void *ptr, size_t len, t_tree *tree)
{
	while (array)
		array++;
	copy_str(array, ptr, len, tree);
}

static void	parse_io(t_cmd *cmd, t_token *tok, t_tree *tree)
{
	void	*src;
	size_t	len;

	src = tok->tok_chars->data;
	len = tok->tok_chars->len;
	if (tok->redirect == RDR_READ)
		copy_redirect(cmd->input, src, len, tree);
	if (tok->redirect == RDR_WRITE || tok->redirect == RDR_APPEND)
		copy_redirect(cmd->output, src, len, tree);
	if (tok->redirect == RDR_HEREDOC)
		copy_str(&cmd->heredoc, src, len, tree);
}

// static void	parse_io(t_cmd *cmd, t_token *tok, t_tree *tree)
// {
// 	void	*src;
// 	size_t	len;
//
// 	src = tok->tok_chars->data;
// 	len = tok->tok_chars->len;
// 	if (tok->redirect == RDR_READ || tok->redirect == RDR_HEREDOC)
// 	{
// 		if (!ft_arena_alloc(tree->arena, (void **)&cmd->input,
// 				(len + 1) * sizeof(char)))
// 			clean_exit(tree, MSG_MALLOCF);
// 		ft_memcpy(cmd->input, src, len * sizeof(char));
// 		cmd->input[len] = '\0';
// 	}
// 	if (tok->redirect == RDR_WRITE || tok->redirect == RDR_APPEND)
// 	{
// 		if (!ft_arena_alloc(tree->arena, (void **)&cmd->output,
// 				(len + 1) * sizeof(char)))
// 			clean_exit(tree, MSG_MALLOCF);
// 		ft_memcpy(cmd->output, src, len * sizeof(char));
// 		cmd->output[len] = '\0';
// 	}
// }
