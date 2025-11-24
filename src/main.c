/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 17:44:16 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/signals.h"
#include "../inc/parsing.h"
#include "../inc/execution.h"
#include <readline/readline.h>
#include <stdlib.h>

extern volatile sig_atomic_t	g_receipt;

static int	handle_flags(int argc, char **argv, t_flag *mode_flag);
static int	minishell(char **envp, t_flag mode_flag);
static void	minishell_init(t_tree *tree);
static int	minishell_reset(t_tree *tree, char **line);
static int	minishell_exit(t_tree *tree, char **line);

int	main(int argc, char **argv, char **envp)
{
	t_flag	mode_flag;
	mode_flag = FLAG_DEFAULT;
	if (argc > 1)
		if (!handle_flags(argc, argv, &mode_flag))
			return (EXIT_SUCCESS);
	if (!minishell(envp, mode_flag))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	handle_flags(int argc, char **argv, t_flag *mode_flag)
{
	int		i;
	t_flag	tmp;

	if (argc == 1)
		return (SUCCESS);
	i = 1;
	while (i < argc)
	{
		tmp = FLAG_DEFAULT;
		if (ft_strcmp(argv[i], "-debug") && ft_strcmp(argv[i], "-envp"))
		{
			ft_putendl_fd(MSG_FLAGPMT, 2);
			return (FAIL);
		}
		if (!ft_strcmp(argv[i], "-debug"))
			tmp = FLAG_DEBUG;
		else if (!ft_strcmp(argv[i], "-envp"))
			tmp = FLAG_ENVP;
		if (tmp == *mode_flag)
			return (FAIL);
		*mode_flag += tmp;
		i++;
	}
	return (SUCCESS);
}

static int	minishell(char **envp, t_flag mode_flag)
{
	char	*line;
	t_tree	tree;

	readline_signals_init(TURN_ON);
	minishell_init(&tree);
	line = NULL;
	while (1)
	{
		if (!minishell_reset(&tree, &line))
			return (FAIL);
		line = readline("cmd> ");
		if (g_receipt == SIGINT || (line && ft_strlen(line) == 0))
			continue ;
		else if (!line || ft_strcmp(line, "exit") == 0)
		{
			if (!minishell_exit(&tree, &line))
				return (FAIL);
			if (mode_flag == FLAG_DEBUG || mode_flag == FLAG_DEBUG_ENVP)
				ft_print_arena_list(tree.a_buf);
			return (SUCCESS);
		}
		add_history(line);
		parser(&tree, line, mode_flag);
		if (!tree.envp)
			envp_init(&tree, envp);
		// TODO: space for executor to run in minishell loop
		// executor(&tree, mode_flag);
		if (mode_flag == FLAG_ENVP || mode_flag == FLAG_DEBUG_ENVP)
			print_envp(&tree);
	}
}

static int	rl_event(void)
{
	if (g_receipt == SIGINT)
	{
		rl_done = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	minishell_init(t_tree *tree)
{
	g_receipt = 0;
	tree->cmd_tab = NULL;
	tree->envp = NULL;
	tree->a_buf = NULL;
	tree->a_sys = NULL;
	rl_event_hook = rl_event;
}

static int	minishell_reset(t_tree *tree, char **line)
{
	g_receipt = 0;
	if (tree->a_buf)
		if (!ft_arena_list_free(&tree->a_buf))
			return (ft_perror(MSG_MALLOCF));
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
			return (ft_perror(MSG_MALLOCF));
	if (tree->a_sys)
		if (!ft_arena_list_free(&tree->a_sys))
			return (ft_perror(MSG_MALLOCF));
	tree->cmd_tab = NULL;
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	rl_clear_history();
	return (SUCCESS);
}
