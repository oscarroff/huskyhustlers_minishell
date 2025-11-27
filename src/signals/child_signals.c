/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:46:24 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/22 12:18:55 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

static void	handle_sig(int signo, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signo == SIGINT)
	{
		g_receipt = EXIT_CTRLC;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		g_receipt = EXIT_CTRLQ;
		// TODO: Figure out which process to kill
		// if (kill(info->si_pid, SIGSEGV) == -1)
		// 	exit(EXIT_FAILURE);
	}
}

void	child_signals_init(int action)
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
