/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:14:19 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/10 11:55:37 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "messages.h"
# include "libft.h"

# define FILE_ACCESS 0644 // Read and write access for the owner

# ifndef PATH_MAX
#  define PATH_MAX          4096
# endif

# ifndef MAXPATHLEN
#  define MAXPATHLEN 1024
# endif

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
	TOK_QUOTATION,
	TOK_REDIRECT,
	TOK_IO,
	TOK_HEREDOC,
	TOK_PIPE,
}	t_tok_type;

typedef enum e_redirect
{
	RDR_DEFAULT,
	RDR_WRITE,
	RDR_APPEND,
	RDR_READ,
	RDR_DELIMITER,
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
	size_t	appendc;
	size_t	len;
}	t_cmdv;

// PARSING
int		parser(t_tree *tree, char *line);
bool	undeniable_logic(t_cmd cmd, t_tree *tree);

// INPUT VALIDATION
int		valid_input(char *line);
bool	ft_isbadsub(char *line);
bool	ft_isquote(char *quote, int c);
bool	ft_isdblpipe(char *line);
bool	ft_isstartpipe(char *line);

// TOKENISER
void	tokenise(t_token *tok, t_redirect *rdr_flag, char *line, t_tree *tree);
void	tokenise_redirect(t_token *tok, char *line);

// HEREDOC
int		heredoc(t_token *tok, t_tree *tree);
int		heredoc_reset(t_tree *tree, char **line);
int		heredoc_clean_exit(t_token *tok, int fd, char *line, t_tree *tree);
int		heredoc_dirty_exit(int fd, char *line, t_tree *tree);

// EXPANDER
void	expandise(t_token *token, t_tree *tree);

// UNQUOTER
void	unquotise(t_token *tok, t_tree *tree);

// COMMANDISER
int		commandise(t_tree *tree, t_vec *tokens);
void	cmd_table_init(t_tree *tree, t_cmdv *vars);
void	cmd_init(t_cmd **cmd, t_cmdv vars, t_tree *tree);
void	cmd_vars_get(t_cmdv *vars, t_vec *tokens, size_t i);
int		cmd_exit(t_tree *tree);

// ENVP
void	envp_init(t_tree *tree, char **envp);
void	envp_key_value_init(t_keyval **dst, t_tree *tree);
int		envp_insert(t_tree *tree, const char *key, size_t len, char *val);
int		envp_search(t_tree *tree, const char *find, size_t len, size_t *key_i);

// UTILS
bool	ft_ismetachar(char c);
int		ft_parse_error(t_tree *tree, char *s);
int		ft_parse_warn(char *s);

#endif
