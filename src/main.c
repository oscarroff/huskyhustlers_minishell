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
#include "debugging.h" //FIXME: Remove for release

volatile sig_atomic_t	g_receipt;

static int	minishell(char **envp, t_flag mode_flag);
static void	minishell_init(t_tree *tree, t_flag mode_flag);
static int	minishell_reset(t_tree *tree, char **line);
static int	minishell_exit(t_tree *tree, char **line);

int	main(int argc, char **argv, char **envp)
{
	t_flag	mode_flag;

	mode_flag = FLAG_DEFAULT;
	if (argc > 1)
		if (!handle_flags(&mode_flag, argc, argv))
			return (EXIT_SUCCESS); //FIXME: Remove for release
	if (!minishell(envp, mode_flag))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	minishell(char **envp, t_flag mode_flag)
{
	char	*line;
	t_tree	tree;

	minishell_init(&tree, mode_flag);
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
		else if (!line || ft_strcmp(line, "exit") == 0)
		{
			if (!minishell_exit(&tree, &line))
				return (FAIL);
			if (tree.mode == FLAG_DEBUG || tree.mode == FLAG_DEBUG_ENVP)
				ft_print_arena_list(tree.a_buf); //FIXME: Remove for release
			return (SUCCESS);
		}
		add_history(line);
		parser(&tree, line);
		if (tree.cmd_tab)
			executor(&tree);
		if (tree.mode == FLAG_ENVP || tree.mode == FLAG_DEBUG_ENVP)
			print_envp(&tree); //FIXME: Remove for release
	}
}

static void	minishell_init(t_tree *tree, t_flag mode_flag)
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
	tree->mode = mode_flag;
	rl_event_hook = rl_event;
}

static int	minishell_reset(t_tree *tree, char **line)
{
	g_receipt = 0;
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
	return (SUCCESS);
}
