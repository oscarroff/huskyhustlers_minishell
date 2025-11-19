/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:07:57 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/19 22:18:02 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "messsages.h"
# include "../libft/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>

extern volatile sig_atomic_t	g_receipt;
typedef struct s_token t_token;

// EMPTY READ (NOTHING TO BE DONE)
# define EMPTY -1

typedef enum e_flag
{
	FLAG_DEFAULT,
	FLAG_DEBUG,
	FLAG_ENVP,
}	t_flag;

typedef struct s_cmd
{
	size_t	argc;
	char	**argv;
	char	**input;
	char	**output;
	char	*heredoc;
}	t_cmd;

typedef struct s_keyval
{
	char	*key;
	char	*value;
}	t_keyval;

typedef struct s_tree
{
	t_vec	*cmd_tab;
	t_vec	*envp;
	t_arena	*arena;
}	t_tree;

// ENVIRONMENT
void	envp_init(t_tree *tree, char **envp, t_flag mode_flag);
int		envp_export(char ***dst, t_tree *tree);
char	*envp_get(char *find, t_tree *tree);

// UTILS
int		ft_superstrdup(char **dst, const char *src, t_arena *arena);
int		ft_superstrndup(char **dst, const char *src, size_t len, t_arena *arena);

// PRINTING
void	print_tokens(t_vec *tokens);
void	print_tokens_vars(t_vec *tokens);
void	print_tok_vars(t_token *tok);
void	print_cmd_tab(t_vec *cmd_tab);
void	print_debugging(t_vec *tokens, t_tree *tree);
void	print_envp(t_vec *envp);

// EXIT
int		ft_perror(char *s);
void	clean_exit(t_tree *tree, char *error);

#endif
