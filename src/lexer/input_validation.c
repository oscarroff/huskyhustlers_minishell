/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/03 19:34:00 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parsing.h"

int	ft_perror(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	write(2, "\n", 1);
	return (KO);
}

int	error_msg(e_error err_msg)
{
	if (err_msg == ERR_OPENQUO)
		return (ft_perror(MSG_OPENQUO));
	if (err_msg == ERR_SYX_GRE)
		return (ft_perror(MSG_SYX_GRE));
	if (err_msg == ERR_SYX_LES)
		return (ft_perror(MSG_SYX_LES));
	if (err_msg == ERR_SYX_PIP)
		return (ft_perror(MSG_SYX_PIP));
	if (err_msg == ERR_MALLOCF)
		return (ft_perror(MSG_MALLOCF));
	return (KO);
}

void	init_lexer(t_tree *tree)
{
	tree->quote = '\0';
	tree->line->data = NULL;
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

// int	char_lexer(int c, t_tree *tree)
// {
// 	return (OK);
// }

int	tokenise_quote(t_tree *tree, char *line, size_t	*start)
{
	t_vec	*token;
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == tree->quote)
			break ;
		i++;
	}
	ft_printf("i is : %u\n", (uint32_t)i);
	if (i > 0)
	{
		ft_print_arena(tree->arena);
		if (!ft_arena_alloc(tree->arena, (void **)&token, sizeof(t_vec)))
			return (KO);
		if (!vec_from(token, line, i, sizeof(char)))
			return (KO);
		if (!vec_push(tree->line, token))
			return (KO);
	}
	*start += i + 1;
	tree->quote = '\0';
	return (OK);
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

int	valid_input(t_tree *tree, char *line)
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
		return (error_msg(tree, ERR_SYX_LES));
	while (i < len)
	{
		ft_isquote(&quote, line[i]);
		if (line[i] == '|')
			if (ft_isdblpipe(line + i))
				return (error_msg(tree, ERR_SYX_PIP));
		i++;
	}
	if (quote != '\0')
		return (error_msg(tree, ERR_OPENQUO));
	return (OK);
}

int	tokenise(t_token *tokens, t_arena *arena, char *line)
{

}

int	lexer(t_tree *tree, char *line)
{
	size_t	i;
	t_token	*token;

	i = 0;
	init_lexer(tree);
	if (!valid_input(tree, line))
		return (KO);
	if (!ft_arena_init(&tree->arena, ARENA_BUF))
		return (error_msg(tree, ERR_MALLOCF));
	while (line && *line && *line != '\0')
	{
		if (!tokenise(token, tree->arena, line))
			return (KO);
		if (!vec_push(tree->tokens, token))
			return (error_msg(tree, ERR_MALLOCF));
		line += token->read_size;
	}
	// if (!vec_new(tree->line, 2, sizeof(t_vec *)))
	// 	return (error_msg(tree, ERR_MALLOCF));
	// while (line[i])
	// {
	// 	if (tree->quote != '\0')
	// 	{
	// 		if (!tokenise_quote(tree, line + i, &i))
	// 			return (error_msg(tree, ERR_MALLOCF));
	// 	}
	// 	else if (ft_isquote(&tree->quote, line[i]) && tree->quote == line[i])
	// 		i++;
	// 	// else if (!char_lexer(line[i], tree))
	// 	// 	return (KO);
	// }
	return (OK);
}

int	parser(t_tree *tree)
{
	(void)tree;
	return (OK);
}

int	main(void)
{
	static char	*line;
	t_tree		tree;
	t_vec		*tmp;

	line = NULL;
	while (1)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline("cmd> ");
		add_history(line);
		// vec_from(&tree.line, line, ft_strlen(line), sizeof(char));
		// vec_printf(&tree.line, 's');
		if (!lexer(&tree, line))
			return (EXIT_FAILURE);
		if (!parser(&tree))
			return (EXIT_FAILURE);
		if (tree.line->data && tree.line->len > 0)
		{
			tmp = *(t_vec **)vec_get(tree.line, 0);
			vec_printf(tmp, 'd');
			vec_free(tree.line);
		}
	}
	return (EXIT_SUCCESS);
}
