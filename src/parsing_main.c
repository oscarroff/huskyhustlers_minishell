/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/10 12:16:00 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"
#include <stdlib.h>

extern volatile sig_atomic_t	g_receipt;

int	main(void)
{
	// sig_init();
	if (!minishell())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	minishell(void)
{
	static char	*line;
	t_tree		tree;

	line = NULL;
	init_minishell(&tree);
	while (1)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline("cmd> ");
		add_history(line);
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		{
			ft_arena_list_free(&tree.arena);
			return (SUCCESS);
		}
		parser(&tree, line);
		// executor(&tree);
	}
}

static void	init_minishell(t_tree *tree)
{
	tree->cmd_tab = NULL;
	tree->arena = NULL;
}

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	ft_printf("Signal received\n");
// }
//
// void	handle_sigquit(int sig)
// {
// 	(void)sig;
// 	ft_printf("Signal received\n");
// }
//
// void	sig_init()
// {
// 	struct sigaction	sa;
//
// 	sa.sa_handler = &handle_sigint;
// 	sa.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// }
