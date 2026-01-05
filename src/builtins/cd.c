/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:27:45 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/05 11:27:46 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

static int get_home(t_exec *exec, char **path);
static void update_pwd(t_tree *tree);

int cd(t_exec *exec)
{
    char        *path;

    if (exec->cmd->argc < 2)
    {
        if (get_home(exec, &path))
            return (ERROR);
    }
    else if (exec->cmd->argc > 2)
    {
        exec->exec_status = exe_err(exec, M_ARGC, (int []){WARN, ERR_GEN});
        return (ERROR);
    }
    else
        path = exec->cmd->argv[1];
    if (chdir(path))
    {
        exec->exec_status = exe_err(exec, path, (int []){WARN, ERR_GEN});
        return (ERROR);
    }
    printf("Changed directory to: %s\n", path);
    update_pwd(exec->tree);
    return (0);
}

static int get_home(t_exec *exec, char **path)
{
    *path = envp_get("HOME", exec->tree);
    if (!*path)
    {
        exec->exec_status = exe_err(exec, M_CDHOME, (int []){WARN, ERR_GEN});
        return (ERROR);
    }
    return (0);
}

static void update_pwd(t_tree *tree)
{
    (void) tree; //need better envp manipulation functions.
    //or use vec_from and vec_insert
}