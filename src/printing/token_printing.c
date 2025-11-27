/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:17:20 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 19:58:38 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	print_type(t_tok_type type);
static void	print_rdr(t_redirect rdr);
static void	print_quote_type(t_quote quote);

void	print_tokens_vars(t_vec *tokens)
{
	t_token	*tok;
	size_t	i;

	write(1, "TOKENS\n", 7);
	i = 0;
	while (i < tokens->len)
	{
		tok = *(t_token **)vec_get(tokens, i);
		print_tok_vars(tok);
		i++;
	}
}

void	print_tok_vars(t_token *tok)
{
	vec_printf_s(tok->tok_chars);
	if (tok->tok_chars->len > 0)
		write(1, " ", 1);
	print_type(tok->type);
	print_rdr(tok->redirect);
	print_quote_type(tok->quote_type);
	write(1, "\n", 1);
}

static void	print_type(t_tok_type type)
{
	if (type == TOK_DEFAULT)
		ft_printf("TOK_DEFAULT ");
	if (type == TOK_COMMAND)
		ft_printf("TOK_COMMAND ");
	if (type == TOK_WORD)
		ft_printf("TOK_WORD ");
	if (type == TOK_QUOTATION)
		ft_printf("TOK_QUOTATION ");
	if (type == TOK_REDIRECT)
		ft_printf("TOK_REDIRECT ");
	if (type == TOK_IO)
		ft_printf("TOK_IO ");
	if (type == TOK_PIPE)
		ft_printf("TOK_PIPE ");
}

static void	print_rdr(t_redirect rdr)
{
	if (rdr == RDR_DEFAULT)
		ft_printf("RDR_DEFAULT ");
	if (rdr == RDR_WRITE)
		ft_printf("RDR_WRITE ");
	if (rdr == RDR_APPEND)
		ft_printf("RDR_APPEND ");
	if (rdr == RDR_READ)
		ft_printf("RDR_READ ");
	if (rdr == RDR_DELIMITER)
		ft_printf("RDR_DELIMITER ");
	if (rdr == RDR_HEREDOC)
		ft_printf("RDR_HEREDOC ");
}

static void	print_quote_type(t_quote quote)
{
	if (quote == QUO_DEFAULT)
		ft_printf("QUO_DEFAULT ");
	if (quote == QUO_SINGLE)
		ft_printf("QUO_SINGLE ");
	if (quote == QUO_DOUBLE)
		ft_printf("QUO_DOUBLE ");
}
