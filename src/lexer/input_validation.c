/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/03 20:42:54 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parsing.h"

int	ft_perror(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	write(2, "\n", 1);
	return (FAIL);
}

int	ft_isquote(char *quote, int c)
{
	if ((c != '"' && c != '\'') || !quote)
		return (0);
	if (c == '"')
	{
		if (*quote == '\0')
			*quote = '"';
		else if (*quote == '"')
			*quote = '\0';
	}
	if (c == '\'')
	{
		if (*quote == '\0')
			*quote = '\'';
		else if (*quote == '\'')
			*quote = '\0';
	}
	return (1);
}

int ft_isdblpipe(char *line)
{
	size_t	i;

	i = 1;
	if (line[i] == '|')
		return (0);
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '|')
		return (1);
	return (0);
}

void	clean_exit(t_tree *tree, char *error)
{
	if (tree)
		if (tree->arena)
			ft_arena_list_free(&tree->arena);
	if (error)
		ft_perror(error);
	exit(EXIT_FAILURE);
}

void	init_lexer(t_token **token, t_tree *tree)
{
	t_token	*new;

	if (!token || !tree)
		clean_exit(tree, MSG_UNITIAL);
	if (!ft_arena_init(&tree->arena, ARENA_BUF))
		clean_exit(tree, "malloc fail 2");
	if (!ft_arena_alloc(tree->arena, (void **)token, sizeof(t_token)))
		clean_exit(tree, "malloc fail 3");
	new = *token;
	if (!vec_alloc(&new->tok_chars, tree->arena))
		clean_exit(tree, "malloc fail 4");
	new->type = TOK_DEFAULT;
	new->quote = '\0';
	new->read_size = 1;
}

int	valid_input(char *line)
{
	size_t	len;
	size_t	i;
	char	quote;

	len = ft_strlen(line);
	i = 0;
	quote = '\0';
	if (ft_strnstr(line, ">>>", len))
		return (ft_perror(MSG_SYX_GRE));
	if (ft_strnstr(line, "<<<", len))
		return (ft_perror(MSG_SYX_LES));
	while (i < len)
	{
		ft_isquote(&quote, line[i]);
		if (line[i] == '|')
			if (ft_isdblpipe(line + i))
				return (ft_perror(MSG_SYX_PIP));
		i++;
	}
	if (quote != '\0')
		return (ft_perror(MSG_OPENQUO));
	return (OK);
}

void	tokenise_quote(t_token *token, char *line, t_tree *tree)
{
	size_t	i;

	token->quote = *line;
	i = 0;
	while (line[i + 1] != token->quote)
		i++;
	if (i > 0)
		if (!vec_from(token->tok_chars, line + 1, i, sizeof(char)))
			clean_exit(tree, "malloc fail 2");
	token->type = TOK_QUOTATION;
	token->read_size = i + 2;
}

void	rdr_set(t_token *tok, e_tok_type type, e_redirect rdr, size_t rd_size)
{
	tok->type = type;
	tok->redirect = rdr;
	tok->read_size = rd_size;
}

void	tokenise_redirect(t_token *token, char *line)
{
	if (*line == '|')
		rdr_set(token, TOK_REDIRECT, RDR_PIPE, 1);
	else if (line[0] == '<' && line[1] != '<')
		rdr_set(token, TOK_REDIRECT, RDR_FILE, 1);
	else if (line[0] == '>' && line[1] != '>')
		rdr_set(token, TOK_REDIRECT, RDR_WRITE, 1);
	else if (line[0] == '<' && line[1] == '<')
		rdr_set(token, TOK_REDIRECT, RDR_FILE_DELIM, 2);
	else if (line[0] == '>' && line[1] == '>')
		rdr_set(token, TOK_REDIRECT, RDR_APPEND, 2);
}

bool	ft_ismetachar(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

void	tokenise_word(t_token *token, char *line, t_tree *tree)
{
	size_t	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]) && !ft_ismetachar(*line))
		i++;
	if (i > 0)
		if (!vec_from(token->tok_chars, line, i, sizeof(char)))
			clean_exit(tree, "malloc fail 2");
	token->type = TOK_WORD;
	token->read_size = i;
}

void	tokenise(t_token *token, char *line, t_tree *tree)
{
	if (!token || !line || !tree)
		clean_exit(tree, MSG_UNITIAL);
	if (*line == '"' || *line == '\'')
		tokenise_quote(token, line, tree);
	else if (ft_ismetachar(*line))
		tokenise_redirect(token, line);
	else
		tokenise_word(token, line, tree);
}

// TODO: WRITE yacc implementation tokens to commands
void	commandise(t_tree *tree, t_token *token)
{
	(void)tree;
	(void)token;
}

int	parser(t_tree *tree, char *line)
{
	t_token	*token;

	if (!tree || !line)
		return (FAIL);
	token = NULL;
	if (!valid_input(line))
		return (FAIL);
	init_lexer(&token, tree);
	while (line && *line && *line != '\0')
	{
		while (ft_isspace(*line))
			line++;
		if (!*line)
			break ;
		tokenise(token, line, tree);
		if (token->tok_chars)
			vec_printf_s(token->tok_chars);
		// ft_printf("Read size: %u\n", (uint32_t)token->read_size);
		commandise(tree, token);
		line += token->read_size;
		vec_reset(token->tok_chars);
	}
	return (SUCCESS);
}

int	executor(t_tree *tree)
{
	(void)tree;
	return (OK);
}

void	init_minishell(t_tree *tree)
{
	tree->cmd_tab = NULL;
	tree->arena = NULL;
}

int	minishell(void)
{
	static char	*line;
	t_tree		tree;

	line = NULL;
	init_minishell(&tree);
	while (1)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline("cmd> ");
		add_history(line);
		parser(&tree, line);
		executor(&tree);
	}
}

int	main(void)
{
	if (!minishell())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
