/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:07:57 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 14:58:48 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>

# define MSG_FLAG_PROMPT "minishell: use the flag '-debug' to enable debugging"

extern volatile sig_atomic_t	g_receipt;

typedef enum	e_flag
{
	FLAG_DEFAULT,
	FLAG_DEBUG,
}	e_flag;

#endif
