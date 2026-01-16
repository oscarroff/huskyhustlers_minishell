/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:34:20 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/05 11:35:24 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"
#include "../../inc/minishell.h"

static bool is_initiated(t_exec *exec, char **in, char **out);
static int	set_heredoc(t_exec *exec);
static int	set_in_file(t_exec *exec, char **in);
static int	set_out_file(t_exec *exec, char **out);

int	get_redirs(t_exec *exec)
{
	char	**in_fs;
	char	**out_fs;

	in_fs = exec->cmd->input;
	out_fs = exec->cmd->output;
	if (in_fs || out_fs || exec->cmd->heredoc)
	{
		if (is_initiated(exec, in_fs, out_fs) == false)
			return (ERROR);
	}
	return (0);
}

static bool	is_initiated(t_exec *exec, char **in, char **out)
{
	if (in && in[0])
	{
		if (set_in_file(exec, in) == ERROR)
			return (false);
	}
	if (exec->cmd->heredoc && exec->cmd->heredoc[0])
	{
		if (set_heredoc(exec) == ERROR)
			return (false);
	}
	if (out && out[0])
	{
		if (set_out_file(exec, out) == ERROR)
			return (false);
	}
	return (true);
}

static int	set_heredoc(t_exec *exec)
{
	int	fd;
	int	o_flag;

	o_flag = O_RDWR | O_CREAT | O_TRUNC;
	if (exec->redir_in != STDIN_FILENO && exec->redir_in != ERROR)
		close(exec->redir_in);
	fd = try_open(exec, "/tmp/heredoc_tmp", o_flag, RW_R__R__);
	try_write_endl(exec->tree, fd, exec->cmd->heredoc);
	close(fd);
	exec->redir_in = try_open(exec, "/tmp/heredoc_tmp", O_RDONLY, 0);
	unlink("/tmp/heredoc_tmp");
	return (exec->redir_in);
}

static int	set_in_file(t_exec *exec, char **in)
{
	char	*file;
	int		i;

	i = 0;
	while (in[i])
		i++;
	file = in[i - 1];
	if (exec->redir_in != STDIN_FILENO && exec->redir_in != ERROR)
		close(exec->redir_in);
	exec->redir_in = try_open(exec, file, O_RDONLY, 0);
	return (exec->redir_in);
}

static int	set_out_file(t_exec *exec, char **out)
{
	t_out	*type;
	int		o_flag;
	int		i;

	i = 0;
	type = exec->cmd->out_type;
	while (out[i])
	{
		if (exec->redir_out != STDOUT_FILENO && exec->redir_out != ERROR)
			close(exec->redir_out);
		o_flag = O_WRONLY | O_CREAT;
		if (type[i] == OUT_APPEND)
			o_flag |= O_APPEND;
		else if (type[i] == OUT_WRITE)
			o_flag |= O_TRUNC;
		exec->redir_out = try_open(exec, out[i], o_flag, RW_RW_RW_);
		i++;
	}
	return (exec->redir_out);
}
