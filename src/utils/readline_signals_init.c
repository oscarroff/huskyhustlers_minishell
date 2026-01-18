/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_signals_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:46:24 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/15 16:31:56 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

int	rl_event(void)
{
	if (g_receipt == SIGINT)
	{
		rl_done = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	handle_sig(int signo, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signo == SIGINT)
		g_receipt = SIGINT;
}

void	readline_signals_init(int action)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	if (action == TURN_ON)
	{
		act.sa_sigaction = handle_sig;
		sigemptyset(&act.sa_mask);
		sigaddset(&act.sa_mask, SIGINT);
		sigaddset(&act.sa_mask, SIGQUIT);
		act.sa_flags = SA_RESTART | SA_SIGINFO;
		sigaction(SIGINT, &act, NULL);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGPIPE, SIG_IGN);
	}
	else
	{
		act.sa_handler = SIG_DFL;
		act.sa_flags = SA_RESTART;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
	}
}
