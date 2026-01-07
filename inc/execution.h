/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:25:14 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/04 16:41:42 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <errno.h>

// PERMISSION FLAGS
# define RW_RW_RW_          0666

// ERROR MODE FLAGS
# define MODE               0
# define CODE               1

// ERROR MODE TYPES
# define FATAL              0
# define WARN               1

// ERROR MESSAGES
# define M_SYS              ": system call failed"
# define M_CMDNF            ": command not found"
# define M_FEXE             ": cannot execute command"
# define M_ARGC             ": too many arguments"
# define M_NUMARG           ": numeric argument required"
# define M_PWDERR           ": cannot retrieve current directory"
# define M_CDHOME           ": HOME not set"

// GENERAL STATUS FLAGS
# define ERROR              -1

// SPECIFIC ERROR CODES
# define ERR_INVALID_EXIT   255
# define ERR_S_TERMINATED   130
# define ERR_EXIT_ARGS128   128
# define ERR_CMDNF          127
# define ERR_CEXEC          126
# define ERR_BTIN           2
# define ERR_GEN            1

# ifndef PATH_MAX
#  define PATH_MAX          4096
# endif

typedef struct s_exec       t_exec;
typedef struct s_verif_path t_veri;

typedef enum e_builtin      t_builtin;

typedef int                 t_func(t_exec *exec);

enum e_builtin
{
    FALSE,
    ECHO,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    EXIT
};

struct s_exec
{
    t_tree      *tree;
    t_cmd       *cmd;
    char        *extern_cmd_path;
    t_builtin   builtin;
    int         pipefd[2];
    pid_t       pid;
    int         redir_in;
    int         redir_out;
    bool        next_exists;
    uint8_t     exec_status;
};

struct s_verif_path
{
    char        **dirlist;
    char        *cmd_name;
    char        *dir;

};

//executor.c
void	executor(t_tree *tree);

//verifier.c
int     verify_cmd(t_exec *exec);

//path_var_verif.c
bool    is_on_path_var(t_exec *exec, char *cmd_name, char *path_variable);

//runner.c
int     run(t_exec *execution, int in);
int     run_builtin(t_exec *exec);

//process_management.c
void    get_pipe(t_exec *exec);
void    set_in_out(t_exec *exec, int in);
void    set_fork(t_exec *exec);
void	set_redirs(t_exec *exec);
void    wait_processes(t_exec *execution, pid_t *pids);

//io_redir.c
void	get_redirs(t_exec *exec);

//exe_cleanup.c
uint8_t exe_err(t_exec *exec, char *msg, int error_data[2]);
void    close_node_fds(t_exec *exec);
void	clean_exit(t_tree *tree, char *error);

    //BUILTINS
//cd.c
int     cd(t_exec *exec);

//echo.c
int     echo(t_exec *exec);

//pwd.c
int     pwd(t_exec *exec);

//export.c
int     export(t_exec *exec);

//unset.c
int     unset(t_exec *exec);

//env.c
int     env(t_exec *exec);

//bexit.c
int     b_exit(t_exec *exec);

#endif
