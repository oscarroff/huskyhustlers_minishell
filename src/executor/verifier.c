#include "../../inc/minishell.h"
#include "../../inc/execution.h"

static t_builtin	is_builtin(char *cmd_name, t_exec *exec);
static int			is_external(char *cmd_name, t_exec *exec);

int	verify_cmd(t_exec *exec)
{
	char		*cmd_name;
	t_cmd		*cmd;

	cmd = exec->cmd;
	if (cmd)
	{
		cmd_name = exec->cmd->argv[0];
		if (is_builtin(cmd_name, exec))
			return (SUCCESS);
		if (is_external(cmd_name, exec))
			return (SUCCESS);
		else
			return (ERROR);
	}
	return (0);
}

static t_builtin	is_builtin(char *cmd_name, t_exec *exec)
{
	t_builtin		select;
	static char		*types[] = {\
NULL, "echo", "cd", "pwd", "export", "unset", "env", "exit"};

	select = 7;
	while (select > 0)
	{
		if (ft_strcmp(types[select], cmd_name) == 0)
			break ;
		select--;
	}
	exec->builtin = select;
	return (select);
}

static int		is_external(char *cmd_name, t_exec *exec)
{
	(void)cmd_name;
	(void)exec;

	return (0); //implement after BUILTIN implementations and testing
}