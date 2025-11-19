/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:14:19 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/19 22:10:19 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "messsages.h"
# include "../libft/inc/libft.h"

// FORWARD DECLARATIONS (Actual definitions in libft.h)
typedef struct s_arena	t_arena;
typedef struct s_vec	t_vec;

typedef enum e_quote
{
	QUO_DEFAULT,
	QUO_SINGLE,
	QUO_DOUBLE,
}	t_quote;

typedef enum e_tok_type
{
	TOK_DEFAULT,
	TOK_COMMAND,
	TOK_WORD,
	TOK_QUOTATION, // Quote or escape character
	TOK_REDIRECT, // Redirect operato
	TOK_IO,
	TOK_PIPE,
}	t_tok_type;

typedef enum e_redirect
{
	RDR_DEFAULT,
	RDR_WRITE,
	RDR_APPEND,
	RDR_READ,
	RDR_HEREDOC,
}	t_redirect;

typedef struct s_token
{
	t_vec		*tok_chars;
	t_tok_type	type;
	t_redirect	redirect;
	t_quote		quote_type;
	char		quote_char;
	bool		expand;
	size_t		read_size;
}	t_token;

typedef struct s_cmdv
{
	size_t	argc;
	size_t	inputc;
	size_t	outputc;
	size_t	len;
}	t_cmdv;

// PARSING
int		parser(t_tree *tree, char *line, t_flag flag);

// INPUT VALIDATION
int		valid_input(char *line);

// TOKENISER
void	tokenise(t_token *tok, t_redirect *rdr_flag, char *line, t_tree *tree);
void	handle_redirect(t_token *tok, char *line);

// EXPANDER
void	expandise(t_token *token, t_tree *tree);

// COMMANDISER
void	commandise(t_tree *tree, t_vec *tokens);
void	init_cmd_table(t_tree *tree, t_cmdv *vars);
void	init_cmd(t_cmd **cmd, t_cmdv vars, t_tree *tree);
void	get_cmd_vars(t_cmdv *vars, t_vec *tokens, size_t i);

// UTILS
bool	ft_ismetachar(char c);

#endif
