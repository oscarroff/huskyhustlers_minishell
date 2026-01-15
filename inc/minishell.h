/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:07:57 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/15 17:03:41 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "signals.h"
# include "messages.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/stat.h>

typedef struct s_token	t_token;

// EMPTY READ (NOTHING TO BE DONE)
# define EMPTY -1

typedef enum e_flag
{
	FLAG_DEFAULT,
	FLAG_DEBUG,
	FLAG_ENVP,
	FLAG_DEBUG_ENVP,
}						t_flag;

typedef enum e_out
{
	OUT_DEFAULT,
	OUT_WRITE,
	OUT_APPEND,
}						t_out;

typedef struct s_cmd
{
	size_t				argc;
	char				**argv;
	char				**input;
	char				**output;
	t_out				*out_type;
	char				*heredoc;
}						t_cmd;

typedef struct s_keyval
{
	char				*key;
	char				*value;
}						t_keyval;

typedef struct s_tree
{
	t_vec				*cmd_tab;
	t_vec				*envp;
	t_arena				*a_sys;
	t_arena				*a_buf;
	int					exit_code;
	int					ms_lvl;
	char				*pwd;
	t_flag				mode;
}						t_tree;

// ENVIRONMENT
int						envp_export(char ***dst, t_tree *tree);
char					*envp_get(char *find, t_tree *tree);
int						envp_set(t_tree *tree, const char *src);
int						envp_unset(t_tree *tree, const char *src);

// UTILS
int						ft_superstrdup(char **dst, const char *src,
							t_arena *arena);
int						ft_superstrndup(char **dst, const char *src, size_t len,
							t_arena *a);

// EXIT
int						ft_perror(t_tree *tree, char *s);
void					exit_parser(t_tree *tree, char *error);
void					clean(t_tree *tree);

// SYSTEM CALL TRIES
void					try_write(t_tree *tree, int fd_out, char *str);
void					try_write_endl(t_tree *tree, int fd_out, char *str);
int						try_open(t_tree *tree, char *f, int o_flag, int p_flag);

#endif
