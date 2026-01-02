#include "../../inc/minishell.h"

void    try_write(t_tree *tree, int fd_out, char *str)
{
    if (str && str[0])
    {
        if (write(fd_out, str, ft_strlen(str)) == -1)
            //clean_exit(tree, "FATAL: write system call failed");  CLEAN_EXIT REMOVED!!!!!
            (void) tree;
    }
}

void    try_write_endl(t_tree *tree, int fd_out, char *str)
{
    if (str && str[0])
    {
        if (write(fd_out, str, ft_strlen(str)) == -1)
            //clean_exit(tree, "FATAL: write system call failed");  CLEAN_EXIT REMOVED!!!!!
            (void) tree;
    }
    if (write(fd_out, "\n", 1) == -1)
        //clean_exit(tree, "FATAL: write system call failed");  CLEAN_EXIT REMOVED!!!!!
        (void) tree;
}

