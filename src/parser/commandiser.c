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

static void	get_cmd_vars(size_t *argc, size_t *len, t_vec *tokens, size_t i);
static void	parse_tokens(t_cmd *cmd, t_vec *tokens, size_t i, t_tree *tree);
static void	parse_argv(t_cmd *cmd, t_token *tok, size_t argi, t_tree *tree);
static void	parse_io(t_cmd *cmd, t_token *tok, t_tree *tree);

void	commandise(t_tree *tree, t_vec *tokens)
{
	t_cmd	*cmd;
	size_t	argc;
	size_t	len;
	size_t	i;

	if (!tree || !tokens)
		return ;
	if (!tree->cmd_tab)
		init_cmd_table(tree);
	i = 0;
	while (i < tokens->len)
	{
		cmd = NULL;
		argc = 0;
		len = 0;
		get_cmd_vars(&argc, &len, tokens, i);
		init_cmd(&cmd, argc, tree);
		parse_tokens(cmd, tokens, i, tree);
		i += len;
		if (i < tokens->len)
			i++;
	}
}

static void	get_cmd_vars(size_t *argc, size_t *len, t_vec *tokens, size_t i)
{
	t_token	*tok;

	while (i < tokens->len)
	{
		tok = *(t_token **)vec_get(tokens, i);
		if (tok->type == TOK_PIPE)
			break ;
		if (tok->type == TOK_WORD || tok->type == TOK_QUOTATION)
			*argc += 1;
		*len += 1;
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
		{
			parse_argv(cmd, tok, argi, tree);
			argi++;
		}
		i++;
	}
}

static void	parse_argv(t_cmd *cmd, t_token *tok, size_t argi, t_tree *tree)
{
	char	*arg;
	void	*src;
	size_t	len;

	src = tok->tok_chars->data;
	len = tok->tok_chars->len;
	if (!ft_arena_alloc(tree->arena, (void **)&arg, (len + 1) * sizeof(char)))
		clean_exit(tree, MSG_MALLOCF);
	ft_memcpy(arg, src, len * sizeof(char));
	arg[len] = '\0';
	cmd->argv[argi] = arg;
}

static void	parse_io(t_cmd *cmd, t_token *tok, t_tree *tree)
{
	void	*src;
	size_t	len;

	src = tok->tok_chars->data;
	len = tok->tok_chars->len;
	if (tok->redirect == RDR_READ || tok->redirect == RDR_HEREDOC)
	{
		if (!ft_arena_alloc(tree->arena, (void **)&cmd->input,
				(len + 1) * sizeof(char)))
			clean_exit(tree, MSG_MALLOCF);
		ft_memcpy(cmd->input, src, len * sizeof(char));
		cmd->input[len] = '\0';
	}
	if (tok->redirect == RDR_WRITE || tok->redirect == RDR_APPEND)
	{
		if (!ft_arena_alloc(tree->arena, (void **)&cmd->output,
				(len + 1) * sizeof(char)))
			clean_exit(tree, MSG_MALLOCF);
		ft_memcpy(cmd->output, src, len * sizeof(char));
		cmd->output[len] = '\0';
	}
}
