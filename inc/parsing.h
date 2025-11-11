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
# define MSG_UNINTAL "unitialised values"
# define MSG_OVERFLO "size_t overflow"
# define MSG_BAD_SUB "bad substitution"

typedef enum e_tok_type
{
	TOK_DEFAULT,
	TOK_COMMAND,
	TOK_WORD,
	TOK_REDIRECT, // Redirect operator
	TOK_QUOTATION // Quote or escape character
}	e_tok_type;

typedef enum e_redirect
{
	RDR_DEFAULT,
	RDR_WRITE,
	RDR_APPEND,
	RDR_FILE,
	RDR_FILE_DELIM,
	RDR_PIPE
}	e_redirect;

typedef struct s_token
{
	t_vec		*tok_chars;
	e_tok_type	type;
	e_redirect	redirect;
	char		quote;
	bool		expand;
	size_t		read_size;
}	t_token;

// typedef enum {
// 	CMD_BIN,
// 	CMD_BUILTIN,
// } e_cmd_type;
//
// typedef enum {
// 	BUI_NONE,
// 	BUI_ECHO,
// 	BUI_CD,
// 	BUI_PWD,
// 	BUI_EXPORT,
// 	BUI_UNSET,
// 	BUI_ENV,
// 	BUI_EXIT
// } e_builtin;

	// e_cmd_type	cmd_type;
	// e_builtin	builtin;

typedef struct s_cmd {
	char	**argv;
	t_vec	*envp;
	char	*input;
	char	*output;
	char	*heredoc;
} t_cmd;

typedef struct s_tree {
	t_vec	*cmd_tab;
	t_arena	*arena;
} t_tree;

// PARSING
int		parser(t_tree *tree, char *line);

// EXIT
int		ft_perror(char *s);
void	clean_exit(t_tree *tree, char *error);

// INPUT VALIDATION
int		valid_input(char *line);

// TOKENISER
void	tokenise(t_token *token, char *line, t_tree *tree);

// EXPANDER
void	expandise(t_token *token, t_tree *tree);

// COMMANDISER
void	commandise(t_tree *tree, t_token *token);

// UTILS
bool	ft_ismetachar(char c);

#endif

