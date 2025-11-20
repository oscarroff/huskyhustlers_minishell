/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:46:24 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/20 12:26:58 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/signals.h"
#include "../../inc/minishell.h"

static void	handle_sig(int sig)
{
	g_receipt = sig;
}

void	init_ms_signals(int	action)
{
	struct sigaction	sa;

	if (action == ON)
	{
		sa.sa_handler = &handle_sig;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = SA_RESTART;
	}
}
