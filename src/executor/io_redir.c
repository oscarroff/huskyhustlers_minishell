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

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

static bool  init_redir(t_exec *exec, char **in, char **out);
static void  set_heredoc(t_exec *exec);
static int   set_in_file(t_exec *exec, char **in);
static int   set_out_file(t_exec *exec, char **out);

void	get_redirs(t_exec *exec)
{
    char    **in_fs;
    char    **out_fs;

    in_fs = exec->cmd->input;
    out_fs = exec->cmd->output;
    if (in_fs || out_fs || exec->cmd->heredoc)
	    init_redir(exec, in_fs, out_fs);
}

static bool    init_redir(t_exec *exec, char **in, char **out)
{
    if (in && in[0])
    {
        if (set_in_file(exec, in) == ERROR)
            return (false);
    }
    if (exec->cmd->heredoc && exec->cmd->heredoc[0])
        set_heredoc(exec);
    if (out && out[0])
    {
        if (set_out_file(exec, out) == ERROR)
             return (false);
    }
    return (true);
}

static void  set_heredoc(t_exec *exec)
{
    int     fd;
    int     o_flag;

    o_flag = O_RDWR | O_CREAT | O_TRUNC;
    if (exec->redir_in != STDIN_FILENO && exec->redir_in != ERROR)
        close(exec->redir_in);
    fd = try_open(exec->tree, "/tmp/heredoc_tmp", o_flag, RW_R__R__);
    try_write_endl(exec->tree, fd, exec->cmd->heredoc);
    close(fd);
    exec->redir_in = try_open(exec->tree, "/tmp/heredoc_tmp", O_RDONLY, 0);
    unlink("/tmp/heredoc_tmp");
}

static int   set_in_file(t_exec *exec, char **in)
{
    char    *file;
    int     i;

    i = 0;
    while (in[i])
        i++;
    file = in[i - 1];
    if (exec->redir_in != STDIN_FILENO && exec->redir_in != ERROR)
        close(exec->redir_in);
    exec->redir_in = try_open(exec->tree, file, O_RDONLY, 0);
    return (exec->redir_in);
}

//TODO 1: Once have access to the out-order, need to ensure the last out file becomes the FD, whether an append or not.
//(currently apps and outs are in their own arrays, and thus their relative order is lost.)
//TODO 2: close all the in-between FDs on chain.
static int   set_out_file(t_exec *exec, char **out)
{
    char    *file;
    t_out   *type;
    int     o_flag;
    int     i;

    i = 0;
    file = NULL;
    type = exec->cmd->out_type;
    while (out[i])
    {
        o_flag = O_WRONLY | O_CREAT;
        if (exec->redir_out != STDOUT_FILENO && exec->redir_out != ERROR)
            close(exec->redir_out);
        if (type[i] == OUT_APPEND)
            o_flag |= O_APPEND;
        else if (type[i] == OUT_WRITE)
            o_flag |= O_TRUNC;
        exec->redir_out = try_open(exec->tree, out[i], o_flag, RW_RW_RW_);
        i++;
    }
    return (exec->redir_out);
}

