/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:27:57 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/05 11:27:58 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"
#include "../../inc/minishell.h"

static void	display_env(t_exec *exec);
static void	get_len(char **envp, unsigned int *len);
static void	output_env(t_exec *exec, char **envp, int fd_out);
static void	insert_var(t_exec *exec);

int	export(t_exec *exec)
{
	if (!exec->cmd->argv[1])
		display_env(exec);
	else
		insert_var(exec);
	return (0);
}

static void	display_env(t_exec *exec)
{
	int				fd_out;
	unsigned int	len;
	char			**envp;

	fd_out = STDOUT_FILENO;
	if (exec->redir_out)
		fd_out = exec->redir_out;
	envp_export(&envp, exec->tree);
	get_len(envp, &len);
	quicksort(envp, 0, len - 1);
	output_env(exec, envp, fd_out);
}

static void	get_len(char **envp, unsigned int *len)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	*len = i;
}

static void	output_env(t_exec *exec, char **envp, int fd_out)
{
	t_tree	*tree;

	tree = exec->tree;
	while (*envp)
	{
		try_write_endl(tree, fd_out, *envp);
		envp++;
	}
}

static void	insert_var(t_exec *exec)
{
	size_t	i;
	char	**args;

	i = 1;
	args = exec->cmd->argv;
	while (args[i])
	{
		if (!envp_set(exec->tree, exec->cmd->argv[i]))
			clean_exit(exec->tree, NULL);
		i++;
	}
}
