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

static inline bool  set_redir(t_exec *exec);
//static inline void  set_heredoc(t_exec *exec);
//static inline int   set_in_f(t_exec *exec);
//static inline int   set_out_f(t_exec *exec);

void	get_redirs(t_exec *exec)
{
    // char    **inputf_chain;
    // char    **outputf_chain;

    // inputf_chain = exec->cmd->input;
    // outputf_chain = exec->cmd->output;
	set_redir(exec);
}

static inline bool    set_redir(t_exec *exec)
{
    (void) exec;
    /*
    if (file doesnt exist:)
        ": ambiguous redirect"
        if type == IN
            redir_in = ERROR;
        if type == OUT
            redir_out = ERROR;
    else
    {
        if type == IN
            if set_in_f() == ERROR
                return false
        if type == HEREDOC
            set_in_heredoc()
        if type == OUT || type == APPEND
            if set_out_f() == ERROR
                return false
    }
    */
    return (true);
}

/*
static inline void  set_heredoc(t_exec *exec)
{
    (void) exec;
    //just route IN the data from heredoc tommy implementation
}

static inline int   set_in_f(t_exec *exec)
{
    //char    *file;

    //file = *exec->cmd->input;
    if (exec->redir_in != STDIN_FILENO && exec->redir_in != ERROR)
        close(exec->redir_in);
    //exec->redir_in = try_open(exec->tree, file, O_RDONLY, 0);
    return (exec->redir_in);
}

static inline int   set_out_f(t_exec *exec)
{
    //char    *file;
    int     o_flag;
    
    //file = *exec->cmd->output;
    o_flag = O_WRONLY | O_CREAT;

    //if type == APPEND
    //    o_flag |= O_APPEND;
    //if type == OUT
    //    o_flag |= O_TRUNC;

    if (exec->redir_out != STDOUT_FILENO && exec->redir_out != ERROR)
        close(exec->redir_out);
    //exec->redir_out = try_open(exec->tree, file, o_flag, RW_RW_RW_);
    return (exec->redir_out);
}
*/
