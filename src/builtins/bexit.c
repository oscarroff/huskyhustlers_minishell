#include "../../inc/minishell.h"
#include "../../inc/execution.h"

//static void         clean(t_tree *tree);  TODO: NEW CLEAN FUNCTION!
static inline bool  is_valid_value(const char *str, uint8_t *status);
static inline bool  is_numeric(const char *str, int *i);

int b_exit(t_exec *exec)
{
    uint8_t     status;

    status = exec->exec_status;
    if (exec->cmd->argv[1])
    {
        if (is_valid_value(exec->cmd->argv[1], &status) == false)
            status = ERR_BTIN;
        else if (exec->cmd->argc > 2)
        {
            exec->exec_status = exe_err(exec, M_ARGC, (int []){WARN, ERR_GEN});
            return (ERR_GEN);
        }
    }
    //clean(exec->tree);
    exit(status);
}

/* FIX: MODIFICATIONS TO ARENAS MADE THIS OUTDATED
static void clean(t_tree *tree)
{
	if (tree)
		if (tree->arena)
			ft_arena_list_free(&tree->arena);
}
*/

static inline bool  is_valid_value(const char *str, uint8_t *status)
{
    int     i;

    i = 0;
    if (is_numeric(str, &i) == false || !*str)
    {
        ft_perror("exit: numeric argument required");
        return (false);
    }
    if (i > 20)
    {
        ft_perror("exit: numeric argument required");
        return (false);
    }
    else
	{
		//*status = ft_super_atoi(str); //APPARENTLY GONE
        (void) status;
	}
	return (true);
}

static inline bool  is_numeric(const char *str, int *i)
{
    if (str[0] == '-' || str[0] == '+')
    {
		(*i)++;
		if (!str[*i])
			return (false);
	}
	while (str[*i])
	{
		if (ft_isdigit(str[*i]) == false)
			return (false);
		(*i)++;
	}
	return (true);
}