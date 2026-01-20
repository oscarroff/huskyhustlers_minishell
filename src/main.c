/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/15 17:05:40 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "parsing.h"
#include "execution.h"

volatile sig_atomic_t	g_receipt;

static int	minishell(char **envp);
static void	minishell_init(t_tree *tree);
static int	minishell_reset(t_tree *tree, char **line);
static int	minishell_exit(t_tree *tree, char **line);

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
		if (!minishell(envp))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	minishell(char **envp)
{
	char	*line;
	t_tree	tree;

	minishell_init(&tree);
	line = NULL;
	while (1)
	{
		if (!minishell_reset(&tree, &line))
			return (FAIL);
		if (!tree.envp)
			envp_init(&tree, envp);
		line = readline("cmd> ");
		if (g_receipt == SIGINT || (line && ft_strlen(line) == 0))
			continue ;
		else if (!line)
		{
			if (!minishell_exit(&tree, &line))
				return (FAIL);
			return (SUCCESS);
		}
		add_history(line);
		parser(&tree, line);
		if (tree.cmd_tab && g_receipt != SIGINT)
			executor(&tree);
	}
}

static void	minishell_init(t_tree *tree)
{
	readline_signals_init(TURN_ON);
	g_receipt = 0;
	tree->cmd_tab = NULL;
	tree->envp = NULL;
	tree->a_buf = NULL;
	tree->a_sys = NULL;
	tree->exit_code = 0;
	tree->ms_lvl = 1;
	tree->pwd = NULL;
	rl_event_hook = rl_event;
}

static int	minishell_reset(t_tree *tree, char **line)
{
	if (g_receipt != 0)
		tree->exit_code = g_receipt + ERR_EXIT_ARGS128;
	g_receipt = 0;
	rl_done = 0;
	if (tree->a_buf)
		if (!ft_arena_list_free(&tree->a_buf))
			return (ft_perror(NULL, MSG_MALLOCF));
	tree->cmd_tab = NULL;
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (SUCCESS);
}

static int	minishell_exit(t_tree *tree, char **line)
{
	if (tree->a_buf)
		if (!ft_arena_list_free(&tree->a_buf))
			return (ft_perror(NULL, MSG_MALLOCF));
	if (tree->a_sys)
		if (!ft_arena_list_free(&tree->a_sys))
			return (ft_perror(NULL, MSG_MALLOCF));
	tree->cmd_tab = NULL;
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	rl_clear_history();
	try_write_endl(tree, STDOUT_FILENO, "exit");
	return (SUCCESS);
}
