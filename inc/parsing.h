/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:14:19 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/03 11:29:10 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// FORWARD DECLARATIONS (Actual definitions in libft.h)
typedef struct s_arena	t_arena;
typedef struct s_vec	t_vec;

// ERROR MESSAGES
# define MSG_OPENQUO "syntax error unmatched quotes"
# define MSG_SYX_GRE "syntax error near unexpected token '>'"
# define MSG_SYX_LES "syntax error near unexpected token '<'"
# define MSG_SYX_PIP "syntax error near unexpected token '|'"
# define MSG_MALLOCF "malloc fail"

typedef enum {
	ERR_NOERROR, // No error
	ERR_DEFAULT, // Leaves previous error message in place
	ERR_OPENQUO, // Unmatched quote
	// ERR_ARG_MAX, // Arguments exceeds ARG_MAX
	// ERR_CMD_NOF, // Command not found
	// ERR_CON_REF, // Connection refused
	// ERR_PERDENY, // Permission denied (file or directory)
	// ERR_SSHDENY, // Permission denied (publickey)
	// ERR_F_D_NOF, // File or directory not found
	// ERR_DIR_NOF, // Directory not found
	// ERR_OVERWRI, // File already exist
	// ERR_OPT_NOF, // Option not found
	// ERR_BFD_NOF, // File descriptor not found, bad fd
	// ERR_SYX_TOK, // Syntax error near unexpected token
	// ERR_SYX_EOF, // Unexpected end of file
	// ERR_SYX_AOP, // Invalid arthmetic operator
	ERR_SYX_GRE, // Too many consecutive '>'
	ERR_SYX_LES, // Too many consecutive '<'
	ERR_SYX_PIP, // Too many consecutive '|'
	// ERR_ZERODIV, // Division by 0
	// ERR_AM_RDIR, // Ambiguous redirect
	// ERR_BAD_SUB, // Bad substitution, unsupported syntax
	// ERR_SIGSEGV, // Segmentation fault
	// ERR_DEV_NOF, // Device not found
	// ERR_RALLOCF, // Resource allocation fail
	ERR_MALLOCF, // Malloc fail, out ofmemory
	// ERR_REM_NOF, // Unable to connect to remote host
} e_error;

// typedef enum {
// 	SPACE,
// 	TAB,
// 	NEWLINE,
// 	PIPE,
// 	AMP,
// 	COLON,
// 	OPEN_BRACKET,
// 	CLOSE_BRACKET,
// 	LESS_THAN,
// 	MORE_THAN
// } e_metachar;

typedef enum {
	TOK_CTRL, // Control operator
	TOK_RDIR, // Redirect operator
	TOK_BTIN, // Builtin command
	TOK_RWRD, // Reserved word
	TOK_QUOT, // Quote or escape character
	TOK_BRAC // Bracket
} e_tok_type;

typedef enum {
	NEW_LINE,
	PIPE,
	DBLPIPE,
	AMP,
	DBLAMP,
	COLON,
	DBLCOLON,
	COLONAMP,
	DBLCOLONAMP,
	PIPEAMP,
	OPEN,
	CLOSE
} e_control;

typedef enum {
	QUOTE_NONE,
	QUOTE_SIN,
	QUOTE_DBL
} e_quote;

typedef enum {
	LESS,
	GREAT,
	DBLLESS,
	DBLGREAT
} e_redirect;

typedef enum {
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
} e_builtin;

// typedef enum {
// } e_resword;

typedef struct s_token {
	// e_metachar	metachar;
	t_vec		*tok_chars;
	e_tok_type	type;
	e_control	ctrl;
	e_redirect	redir;
	e_builtin	builtin;
	int			read_size;
	// e_resword	resword;
} t_token;

typedef struct s_cmd {
	// e_metachar	metachar;
	t_vec		*command;
	t_vec		*args;
	t_vec		*redirects;
	e_tok_type	type;
	e_control	ctrl;
	e_redirect	redir;
	e_builtin	builtin;
	// e_resword	resword;
} t_cmd;

typedef struct s_tree {
	e_error	error;
	t_vec	*tokens;
	t_arena	*arena;
	char	quote;
} t_tree;

int	error_msg(e_error err_msg);

#endif

