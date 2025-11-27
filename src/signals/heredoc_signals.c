/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:46:24 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 20:17:17 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "signals.h"
//
// static void	handle_sig(int signo, siginfo_t *info, void *context)
// {
// 	(void)signo;
// 	(void)context;
// 	(void)info;
// 	g_receipt = EXIT_CTRLC;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }
//
// void	heredoc_signals_init(int action)
// {
// 	struct sigaction	act;
//
// 	ft_memset(&act, 0, sizeof(act));
// 	if (action == TURN_ON)
// 	{
// 		act.sa_sigaction = handle_sig;
// 		sigemptyset(&act.sa_mask);
// 		sigaddset(&act.sa_mask, SIGINT);
// 		act.sa_flags = SA_RESTART | SA_SIGINFO;
// 		sigaction(SIGINT, &act, NULL);
// 	}
// 	else
// 	{
// 		act.sa_handler = SIG_DFL;
// 		act.sa_flags = SA_RESTART;
// 	}
// }
