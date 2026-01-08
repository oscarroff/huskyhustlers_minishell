/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:27:53 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/05 11:27:54 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

static void print_env(t_tree *tree, char *env);

int env(t_exec *exec)
{
    char    *arg;
    char    **envp;
    size_t  i;

    if (!exec)
        return (ERROR);
    arg = exec->cmd->argv[1];
    if (arg)
    {
        exec->exec_status = exe_err(exec, arg, (int []){WARN, ERR_CMDNF});
        return (ERROR);
    }
    envp = NULL;
    if (!envp_export(&envp, exec->tree))
        return (ERROR);
    i = 0;
    while (envp[i])
        print_env(exec->tree, envp[i++]);
    return (0);
}

static void print_env(t_tree *tree, char *env)
{
    int         fd_out;

    fd_out = STDOUT_FILENO;
    try_write_endl(tree, fd_out, env);
}
