/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:14:19 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/03 21:51:24 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// FORWARD DECLARATIONS (Actual definitions in libft.h)
typedef struct s_arena	t_arena;
typedef struct s_vec	t_vec;

typedef enum {
	CMD_BIN,
	CMD_BUILTIN,
	CMD_EXIT_STATUS
} e_cmd_type;

typedef enum {
	RDR_DEFAULT,
	RDR_WRITE,
	RDR_APPEND,
	RDR_FILE,
	RDR_FILE_DELIM,
	RDR_PIPE
} e_redirect;

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

#endif

