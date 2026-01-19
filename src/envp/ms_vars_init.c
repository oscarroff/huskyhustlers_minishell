/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_vars_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:18:35 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/16 13:49:45 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	set_pwd(char **dst, t_tree *tree);
static int	set_shlvl(char **dst, t_tree *tree);

int	ms_vars_init(t_tree *tree)
{
	char		*pwd;
	char		*shlvl;

	pwd = NULL;
	shlvl = NULL;
	if (!set_shlvl(&shlvl, tree) || !set_pwd(&pwd, tree))
		return (FAIL);
	if (!envp_insert(tree, "PWD", 3, pwd)
		|| !envp_insert(tree, "SHLVL", 5, shlvl))
		return (FAIL);
	return (SUCCESS);
}

static int	set_pwd(char **dst, t_tree *tree)
{
	char	buf[PATH_MAX];
	char	*pwd;

	pwd = envp_get("PWD", tree);
	if (!pwd)
		pwd = getcwd(buf, sizeof(buf));
	else
		if (!ft_superstrdup(&tree->pwd, pwd, tree->a_sys))
			return (FAIL);
	if (!pwd)
	{
		if (errno == ENOENT)
			ft_parse_warn(NULL, MSG_VIKILOG, 0, tree);
		else
			exit_parser(tree, MSG_SYSCALL);
	}
	*dst = pwd;
	return (SUCCESS);
}

static int	set_shlvl(char **dst, t_tree *tree)
{
	char	*shlvl;

	shlvl = envp_get("SHLVL", tree);
	if (!shlvl)
	{
		if (!ft_superstrdup(&shlvl, "1", tree->a_sys))
			return (FAIL);
		tree->ms_lvl = 1;
	}
	else
	{
		if (!ft_atoi(shlvl, &tree->ms_lvl))
			return (FAIL);
		tree->ms_lvl++;
		ft_superitoa(&shlvl, tree->ms_lvl, tree->a_sys);
	}
	*dst = shlvl;
	return (SUCCESS);
}
