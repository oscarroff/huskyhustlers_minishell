/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:03:45 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/19 22:11:20 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

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
	while (i < tokens->len)
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
}

static void	parse_argv(t_cmd *cmd, t_token *tok, size_t argi, t_tree *tree)
{
	char	*arg;
	void	*src;
	size_t	len;

	src = tok->tok_chars->data;
	len = tok->tok_chars->len;
	arg = NULL;
	ft_superstrndup(&arg, src, len, tree->arena);
	arg[len] = '\0';
	cmd->argv[argi] = arg;
	cmd->argv[argi + 1] = NULL;
}

static void	copy_redirect(char **array, void *ptr, size_t len, t_tree *tree)
{
	while (*array)
		array++;
	ft_superstrndup(array, ptr, len, tree->arena);
	array++;
	*array = NULL;
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
		ft_superstrndup(&cmd->heredoc, src, len, tree->arena);
}
