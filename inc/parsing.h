/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:14:19 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/10 12:04:48 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/inc/libft.h"

// FORWARD DECLARATIONS (Actual definitions in libft.h)
typedef struct s_arena	t_arena;
typedef struct s_vec	t_vec;

// ERROR MESSAGES
# define MSG_OPENQUO "syntax error unmatched quotes"
# define MSG_SYX_GRE "syntax error near unexpected token '>'"
# define MSG_SYX_LES "syntax error near unexpected token '<'"
# define MSG_SYX_PIP "syntax error near unexpected token '|'"
# define MSG_MALLOCF "malloc fail"
# define MSG_UNITIAL "unitialised values"
# define MSG_OVERFLO "size_t overflow"

typedef enum {
	ERR_NOERROR, // No error
	ERR_DEFAULT, // Leaves previous error message in place
	ERR_OPENQUO, // Unmatched quote
	// ERR_ARG_MAX, // Arguments exceeds ARG_MAX
	// ERR_CMD_NOF, // Command not found
	// ERR_CTR_REF, // Connection refused
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
// 	QUO_NONE,
// 	QUO_SINGLE,
// 	QUO_DOUBLE
// } e_quote;

// typedef enum {
// 	CTR_NONE,
// 	CTR_NEW_LINE,
// 	CTR_PIPE,
// 	CTR_DBLPIPE,
// 	CTR_AMP,
// 	CTR_DBLAMP,
// 	CTR_COLON,
// 	CTR_DBLCOLON,
// 	CTR_COLONAMP,
// 	CTR_DBLCOLONAMP,
// 	CTR_PIPEAMP,
// 	CTR_OPEN,
// 	CTR_CLOSE
// } e_control;

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

// typedef enum {
// 	RDR_NONE,
// 	RDR_LESS,
// 	RDR_GREAT,
// 	RDR_DBLLESS,
// 	RDR_DBLGREAT
// } e_redirect;

// typedef enum {
// 	TOK_DEFAULT,
// 	TOK_COMMAND,
// 	TOK_CONTROL, // Control operator
// 	TOK_REDIRECT, // Redirect operator
// 	TOK_BUILTIN, // Builtin command
// 	TOK_RESERVED, // Reserved word
// 	TOK_QUOTATION, // Quote or escape character
// 	TOK_BRACET // Bracket
// } e_tok_type;

typedef enum {
	TOK_DEFAULT,
	TOK_WORD,
	TOK_REDIRECT, // Redirect operator
	TOK_QUOTATION // Quote or escape character
} e_tok_type;

typedef enum {
	RDR_DEFAULT,
	RDR_WRITE,
	RDR_APPEND,
	RDR_FILE,
	RDR_FILE_DELIM,
	RDR_PIPE
} e_redirect;

typedef struct s_token {
	t_vec		*tok_chars;
	e_tok_type	type;
	e_redirect	redirect;
	char		quote;
	bool		expand;
	size_t		read_size;
	// e_control	ctrl;
	// e_redirect	redir;
	// e_builtin	builtin;
} t_token;

typedef enum {
	CMD_BIN,
	CMD_BUILTIN,
} e_cmd_type;

typedef enum {
	BUI_NONE,
	BUI_ECHO,
	BUI_CD,
	BUI_PWD,
	BUI_EXPORT,
	BUI_UNSET,
	BUI_ENV,
	BUI_EXIT
} e_builtin;

typedef struct s_cmd {
	t_vec		*cmd;
	t_vec		*args;
	e_cmd_type	cmd_type;
	e_builtin	builtin;
	e_redirect	input;
	e_redirect	ouput;
} t_cmd;

typedef struct s_tree {
	t_vec	*cmd_tab;
	t_arena	*arena;
} t_tree;

// PARSING
int		parser(t_tree *tree, char *line);
void	init_lexer(t_token **token, t_tree *tree);

// EXIT
int		ft_perror(char *s);
void	clean_exit(t_tree *tree, char *error);

// INPUT VALIDATION
int		valid_input(char *line);
int		ft_isdblpipe(char *line);
int		ft_isquote(char *quote, int c);

// TOKENISER
void	tokenise(t_token *token, char *line, t_tree *tree);
void	tokenise_quote(t_token *token, char *line, t_tree *tree);
void	tokenise_redirect(t_token *token, char *line);
void	rdr_set(t_token *tok, e_tok_type type, e_redirect rdr, size_t rd_size);
void	tokenise_word(t_token *token, char *line, t_tree *tree);

// EXPANDER
void	expandise(t_token *token, t_tree *tree);
size_t	parse_expansion(t_token *token, size_t i, t_tree *tree);
size_t	exp_len(size_t *start, bool *braces, t_token *token, size_t i);
void	expand_env_var(t_vec *tmp, t_tree *tree);
void	remove_exp(t_token *token, size_t *start, size_t len, bool braces);

// COMMANDISER
void	commandise(t_tree *tree, t_token *token);

#endif

