/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:25:14 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/20 17:06:42 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"
# include "libft.h"

# define TURN_ON 1
# define TURN_OFF 0

# define EXIT_CTRLD 0 // 0 for success
# define EXIT_CTRLC 130 // 130 for 128 + 2 (2 is SIGINT)
# define EXIT_CTRLQ 134 // 134 for 128 + 8 (8 is SIGQUIT)

// SIGNALS
void	readline_signals_init(int action);

#endif
