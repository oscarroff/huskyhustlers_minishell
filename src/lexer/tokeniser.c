/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:50:59 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/10 16:40:16 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	tokenise_word(t_token *tok, char *line, t_tree *tree);
static void	tokenise_io_pair(t_token *tok, t_redirect *rdr_flag);

void	tokenise(t_parse *p, t_tree *tree)
{
	size_t	i;
	//t_token *tok, t_redirect *rdr_flag, char *line;

	i = 0;
	ft_printf("I got here\n");
	if (!p || !tree)
		exit_parser(tree, MSG_UNINTAL);
	ft_printf("I got here\n");
	while (ft_isspace(p->line[i]))
		i++;
	if (ft_ismetachar(p->line[i]))
		tokenise_redirect(p->tok, p->line + i);
	else
		tokenise_word(p->tok, p->line + i, tree);
	tokenise_io_pair(p->tok, &p->rdr_flag);
	if (p->tok->type == TOK_IO && p->tok->redirect == RDR_HEREDOC)
		heredoc(p->tok, tree);
	p->tok->read_size += i;
}

static void	tokenise_word(t_token *tok, char *line, t_tree *tree)
{
	size_t	i;

	i = 0;
	while (line[i] && !ft_ismetachar(line[i])
		&& (!ft_isspace(line[i]) || tok->quote_char != '\0'))
	{
		// FIXME: Unnecessary? tok->expand no longer used by expander
		// if (line[i] == '$' && tok->expand == false)
		// 	tok->expand = true;
		ft_isquote(&tok->quote_char, line[i]);
		i++;
	}
	if (i > 0)
	{
		if (!vec_from(tok->tok_chars, line, i, sizeof(char)))
			exit_parser(tree, MSG_MALLOCF);
	}
	while (ft_isspace(line[i]))
		i++;
	tok->type = TOK_WORD;
	tok->read_size = i;
	tok->quote_char = '\0';
}

static void	tokenise_io_pair(t_token *tok, t_redirect *rdr_flag)
{
	if (*rdr_flag != RDR_DEFAULT)
	{
		// ft_printf("resetting flag\n");
		tok->type = TOK_IO;
		tok->redirect = *rdr_flag;
		*rdr_flag = RDR_DEFAULT;
	}
	else if (*rdr_flag == RDR_DEFAULT && tok->type == TOK_REDIRECT)
	{
		// ft_printf("setting flag\n");
		*rdr_flag = tok->redirect;
	}
}
