/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:28:20 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/05 11:35:27 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"
#include "../../inc/minishell.h"

uint8_t	exe_err(t_exec *exec, char *msg, int error_data[2])
{
	char	*cmd;
	char	*full_msg;
	uint8_t	status;

	if (error_data[MODE] == FATAL)
		clean_exit(exec->tree, msg);
	status = error_data[CODE];
	cmd = exec->cmd->argv[0];
	full_msg = ft_strjoin(cmd, msg);
	ft_perror(NULL, full_msg);
	free(full_msg);
	return (status);
}

void	close_node_fds(t_exec *exec)
{
	if (exec->redir_in != STDIN_FILENO && exec->redir_in != ERROR)
		close(exec->redir_in);
	if (exec->redir_out != STDOUT_FILENO && exec->redir_out != ERROR)
		close(exec->redir_out);
}

void	clean_exit(t_tree *tree, char *error)
{
	uint8_t	status;

	clean(tree);
	if (error)
	{
		perror(error);
		status = EXIT_FAILURE;
	}
	else if (errno)
	{
		perror("minishell");
		errno = 0;
		status = EXIT_FAILURE;
	}
	else
		status = 0;
	exit(status);
}
