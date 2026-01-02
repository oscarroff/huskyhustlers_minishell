#include "../../inc/minishell.h"
#include "../../inc/execution.h"

uint8_t exe_err(t_exec *exec, char *msg, int error_data[2])
{
    char        *cmd;
    char        *full_msg;
    uint8_t     status;

    status = error_data[CODE];
    //if (error_data[MODE] == FATAL)
    //    clean_exit(exec->tree, msg);  CLEAN_EXIT REMOVED!!!!
    cmd = exec->cmd->argv[0];
    full_msg = ft_strjoin(cmd, msg);
    ft_perror(full_msg);
    free(full_msg);
    return (status);
}