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

int	main(void)
{
	if (!minishell())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	minishell(void)
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
		parser(&tree, line);
		// executor(&tree);
	}
}

void	init_minishell(t_tree *tree)
{
	tree->cmd_tab = NULL;
	tree->arena = NULL;
}

void	signal_handler(int sig)
{
	(void)sig;
	ft_printf("Signal received\n");
}

// int	main(int argc, char **argv)
// {
// 	struct sigaction	sa;
//
// 	sa.sa_handler = &signal_handler;
// 	return (EXIT_SUCCESS);
// }
