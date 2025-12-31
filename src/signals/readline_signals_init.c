/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_signals_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:46:24 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/27 14:10:31 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
// #include "minishell.h"

static void	handle_sig(int signo, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signo == SIGINT)
	{
		g_receipt = SIGINT;
	}
	if (signo == SIGQUIT)
	{
		g_receipt = SIGQUIT;
		// TODO: Figure out which process to kill
		// if (kill(info->si_pid, SIGSEGV) == -1)
		// 	exit(EXIT_FAILURE);
	}
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
		sigaction(SIGQUIT, &act, NULL);
	}
	else
	{
		act.sa_handler = SIG_DFL;
		act.sa_flags = SA_RESTART;
	}
}
