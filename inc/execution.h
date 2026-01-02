/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:25:14 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/02 16:16:31 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "../libft/inc/libft.h"
# include <errno.h>

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
    t_builtin   builtin;
    int         pipefd[2];
    pid_t       pid;
    int         redir_in;
    int         redir_out;
    bool        next_exists;
    uint8_t     exec_status;
};

//executor.c
void	executor(t_tree *tree, t_flag mode_flag);
void    wait(t_exec execution);

//verifier.c
int     verify_cmd(t_exec *exec);

//runner.c
int     run(t_exec *execution);

//process_management.c
void    get_pipe(t_exec *exec);
void    set_in_out(t_exec *exec);
void    set_fork(t_exec *exec);

//exe_errors.c
uint8_t exe_err(t_exec *exec, char *msg, int error_data[2]);

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
