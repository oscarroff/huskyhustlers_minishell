/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 15:04:34 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

extern volatile sig_atomic_t	g_receipt;

static int	parse_args(int argc, char **argv, e_flag *flag);
static int	minishell(e_flag flag);
static void	init_minishell(t_tree *tree);
static int	reset_minishell(t_tree *tree, char **line);

int	main(int argc, char **argv)
{
	e_flag	flag;
	// sig_init();
	flag = FLAG_DEFAULT;
	if (argc > 1)
		if (!parse_args(argc, argv, &flag))
			return (EXIT_SUCCESS);
	if (!minishell(flag))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	parse_args(int argc, char **argv, e_flag *flag)
{
	if (argc > 2 || ft_strcmp(argv[1], "-debug"))
	{
		ft_putendl_fd(MSG_FLAG_PROMPT, 2);
		return (FAIL);
	}
	if (!ft_strcmp(argv[1], "-debug"))
		*flag = FLAG_DEBUG;
	return (SUCCESS);
}

static int	minishell(e_flag flag)
{
	char	*line;
	t_tree	tree;

	line = NULL;
	init_minishell(&tree);
	while (1)
	{
		if (!reset_minishell(&tree, &line))
			return (FAIL);
		line = readline("cmd> ");
		add_history(line);
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		{
			ft_arena_list_free(&tree.arena);
			return (SUCCESS);
		}
		parser(&tree, line, flag);
		// executor(&tree);
	}
}

static void	init_minishell(t_tree *tree)
{
	tree->cmd_tab = NULL;
	tree->arena = NULL;
}

static int	reset_minishell(t_tree *tree, char **line)
{
	if (tree->arena)
		if (!ft_arena_list_free(&tree->arena))
			return (ft_perror(MSG_MALLOCF));
	tree->cmd_tab = NULL;
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (SUCCESS);
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
