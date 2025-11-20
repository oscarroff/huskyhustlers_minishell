/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/20 12:00:00 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/signals.h"
#include "../inc/parsing.h"
#include "../inc/execution.h"

extern volatile sig_atomic_t	g_receipt;

static int	parse_args(int argc, char **argv, t_flag *mode_flag);
static int	minishell(char **envp, t_flag mode_flag);
static void	init_minishell(t_tree *tree);
static int	reset_minishell(t_tree *tree, char **line);

int	main(int argc, char **argv, char **envp)
{
	t_flag	mode_flag;
	// sig_init();
	mode_flag = FLAG_DEFAULT;
	if (argc > 1)
		if (!parse_args(argc, argv, &mode_flag))
			return (EXIT_SUCCESS);
	if (!minishell(envp, mode_flag))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	parse_args(int argc, char **argv, t_flag *mode_flag)
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

	line = NULL;
	// TODO: Build ctrl-C, D and \ handling
	// init_signals();
	init_minishell(&tree);
	while (1)
	{
		if (!reset_minishell(&tree, &line))
			return (FAIL);
		line = readline("cmd> ");
		add_history(line);
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		{
			if (!reset_minishell(&tree, &line))
				return (FAIL);
			if (mode_flag == FLAG_DEBUG || mode_flag == FLAG_DEBUG_ENVP)
				ft_print_arena_list(tree.arena);
			return (SUCCESS);
		}
		parser(&tree, line, mode_flag);
		if (!tree.envp)
			envp_init(&tree, envp, mode_flag);
		// TODO: space for executor to run in minishell loop
		// executor(&tree, mode_flag);
	}
}

static void	init_minishell(t_tree *tree)
{
	tree->cmd_tab = NULL;
	tree->envp = NULL;
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
