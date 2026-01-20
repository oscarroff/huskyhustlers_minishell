/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:27:45 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/15 16:26:07 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parsing.h"

static int	get_home(t_exec *exec, char **path);
static void	update_pwd(t_tree *tree);

int	cd(t_exec *exec)
{
	char	*path;

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
		exec->exec_status = exe_err(exec, M_CHDIR, (int []){WARN_CD, ERR_GEN});
		return (ERROR);
	}
	update_pwd(exec->tree);
	return (0);
}

static int	get_home(t_exec *exec, char **path)
{
	*path = envp_get("HOME", exec->tree);
	if (!*path)
	{
		exec->exec_status = exe_err(exec, M_CDHOME, (int []){WARN, ERR_GEN});
		return (ERROR);
	}
	return (0);
}

static void	update_pwd(t_tree *tree)
{
	char	*tmp;
	char	*pwd;
	char	buf[PATH_MAX];

	pwd = NULL;
	tmp = getcwd(buf, sizeof(buf));
	if (!ft_superstrdup(&pwd, tmp, tree->a_sys))
		clean_exit(tree, NULL);
	if (!pwd)
	{
		if (errno == ENOENT)
			ft_parse_warn(NULL, MSG_VIKILOG, 0, tree);
		else
			exit_parser(tree, MSG_SYSCALL);
	}
	envp_insert(tree, "PWD", 3, pwd);
}
