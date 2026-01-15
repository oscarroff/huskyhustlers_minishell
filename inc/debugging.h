/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:02:09 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/15 17:09:54 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGGING_H
# define DEBUGGING_H

# include "minishell.h"

// FLAG HANDLING
int		handle_flags(t_flag *mode_flag, int argc, char **argv);

// PRINTING
void	print_tokens(t_vec *tokens);
void	print_tokens_vars(t_vec *tokens);
void	print_tok_vars(t_token *tok);
void	print_cmd_tab(t_vec *cmd_tab);
void	print_debugging(t_vec *tokens, t_tree *tree);
void	print_envp(t_tree *tree);

#endif
