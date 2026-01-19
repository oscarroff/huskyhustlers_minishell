/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:25:14 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/15 16:33:58 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "libft.h"
# include <signal.h>

# define TURN_ON 1
# define TURN_OFF 0

# define EXIT_CTRLD 0 // 0 for success
# define EXIT_CTRLC 130 // 130 for 128 + 2 (2 is SIGINT)
# define EXIT_CTRLQ 134 // 134 for 128 + 8 (8 is SIGQUIT)

extern volatile sig_atomic_t	g_receipt;

// SIGNALS
int					rl_event(void);
void				readline_signals_init(int action);
void				heredoc_signals_init(int action);

#endif
