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

static bool  set_redir(t_exec *exec, char **in, char **out, char **app);
static void  set_heredoc(t_exec *exec);
static int   set_in_file(t_exec *exec, char **in);
static int   set_out_file(t_exec *exec, char **out, char **app);

void	get_redirs(t_exec *exec)
{
    char    **input_fs;
    char    **output_fs;
    char    **append_fs;

    input_fs = exec->cmd->input;
    output_fs = exec->cmd->output;
    append_fs =  exec->cmd->append;
	set_redir(exec, input_fs, output_fs, append_fs);
}

static bool    set_redir(t_exec *exec, char **in, char **out, char **app)
{
    if (in[0])
    {
        if (set_in_file(exec, in) == ERROR)
            return (false);
    }
    if (exec->cmd->heredoc[0])
        set_heredoc(exec);
    if (out[0] || app[0])
    {
        if (set_out_file(exec, out, app) == ERROR)
             return (false);
    }
    return (true);
}

static void  set_heredoc(t_exec *exec)
{
    (void) exec;
    //just route IN the data from heredoc tommy implementation
}

static int   set_in_file(t_exec *exec, char **in)
{
    char    *file;

    file = in[0];
    if (exec->redir_in != STDIN_FILENO && exec->redir_in != ERROR)
        close(exec->redir_in);
    exec->redir_in = try_open(exec->tree, file, O_RDONLY, 0);
    return (exec->redir_in);
}

static int   set_out_file(t_exec *exec, char **out, char **app)
{
    char    *file;
    int     o_flag;
    
    o_flag = O_WRONLY | O_CREAT;
    if (app[0])
    {
        file = app[0];
        o_flag |= O_APPEND;
    }
    if (out[0])
    {
        file = out[0];
        o_flag |= O_TRUNC;
    }
    if (exec->redir_out != STDOUT_FILENO && exec->redir_out != ERROR)
        close(exec->redir_out);
    exec->redir_out = try_open(exec->tree, file, o_flag, RW_RW_RW_);
    return (exec->redir_out);
}

