/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:07:57 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/10 11:54:44 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "parsing.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>

// CODES FOR ERROR TRACKING
// SUCCESSFUL EXECUTION
# define OK 1
// UNSUCCEFUL EXECUTION
# define KO 0

// MAIN
int		minishell(void);
void	init_minishell(t_tree *tree);
void	signal_handler(int sig);

// ISCHECKS
bool	ft_ismetachar(char c);

#endif
