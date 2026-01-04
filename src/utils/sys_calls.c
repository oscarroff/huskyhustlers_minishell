#include "../../inc/minishell.h"

void    try_write(t_tree *tree, int fd_out, char *str)
{
    if (str && str[0])
    {
        if (write(fd_out, str, ft_strlen(str)) == -1)
            //clean_exit(tree, "system call failed");  CLEAN_EXIT REMOVED!!!!!
            (void) tree;
    }
}

void    try_write_endl(t_tree *tree, int fd_out, char *str)
{
    if (str && str[0])
    {
        if (write(fd_out, str, ft_strlen(str)) == -1)
            //clean_exit(tree, "system call failed");  CLEAN_EXIT REMOVED!!!!!
            (void) tree;
    }
    if (write(fd_out, "\n", 1) == -1)
        //clean_exit(tree, "system call failed");  CLEAN_EXIT REMOVED!!!!!
        (void) tree;
}

int     try_open(t_tree *tree, char *f, int o_flag, int p_flag)
{
    int     fd;

    fd = open(f, o_flag, p_flag);
    if (fd == -1)
    {
        (void) tree;
        //clean_exit(tree, "system call failed");  CLEAN_EXIT REMOVED!!!!!
    }
    return (fd);
}