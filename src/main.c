/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 21:02:56 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "parsing.h"
#include "execution.h"

extern volatile sig_atomic_t	g_receipt;

static int	handle_flags(t_flag *mode_flag, int argc, char **argv);
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
			return (EXIT_SUCCESS);
	if (!minishell(envp, mode_flag))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	handle_flags(t_flag *mode_flag, int argc, char **argv)
{
	int		i;
	t_flag	tmp;

	if (argc == 1)
		return (SUCCESS);
	i = 1;
	while (i < argc)
	{
		tmp = FLAG_DEFAULT;
		if (ft_strcmp(argv[i], "-debug") && ft_strcmp(argv[i], "-envp")
		&& ft_strcmp(argv[i], "-d") && ft_strcmp(argv[i], "-e"))
		{
			ft_putendl_fd(MSG_FLAGPMT, 2);
			return (FAIL);
		}
		if (!ft_strcmp(argv[i], "-debug") || !ft_strcmp(argv[i], "-d"))
			tmp = FLAG_DEBUG;
		else if (!ft_strcmp(argv[i], "-envp") || !ft_strcmp(argv[i], "-e"))
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
	minishell_init(&tree, mode_flag);
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
			if (tree.mode == FLAG_DEBUG || tree.mode == FLAG_DEBUG_ENVP)
				ft_print_arena_list(tree.a_buf);
			return (SUCCESS);
		}
		add_history(line);
		parser(&tree, line);
		if (!tree.envp)
			envp_init(&tree, envp);
		// TODO: space for executor to run in minishell loop
		// executor(&tree, mode_flag);
		if (tree.mode == FLAG_ENVP || tree.mode == FLAG_DEBUG_ENVP)
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

static void	minishell_init(t_tree *tree, t_flag mode_flag)
{
	g_receipt = 0;
	tree->cmd_tab = NULL;
	tree->envp = NULL;
	tree->a_buf = NULL;
	tree->a_sys = NULL;
	tree->exit_code = 0;
	tree->mode = mode_flag;
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
