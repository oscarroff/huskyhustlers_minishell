/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_calls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:27:11 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/05 11:35:29 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/execution.h"

void    try_write(t_tree *tree, int fd_out, char *str)
{
    if (str && str[0])
    {
        if (write(fd_out, str, ft_strlen(str)) == -1)
        {
            if (tree)
                clean_exit(tree, MSG_SYSCALL);
        }
    }
}

void    try_write_endl(t_tree *tree, int fd_out, char *str)
{
    if (str && str[0])
    {
        if (write(fd_out, str, ft_strlen(str)) == -1)
        {
            if (tree)
                clean_exit(tree, MSG_SYSCALL);
        }
    }
    if (write(fd_out, "\n", 1) == -1)
    {
        if (tree)
            clean_exit(tree, MSG_SYSCALL);
    }
}

int     try_open(t_tree *tree, char *f, int o_flag, int p_flag)
{
    int     fd;

    fd = open(f, o_flag, p_flag);
    if (fd == -1)
    {
        if (tree)
            clean_exit(tree, MSG_SYSCALL);
    }
    return (fd);
}