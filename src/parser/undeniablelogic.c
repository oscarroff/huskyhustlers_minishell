/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undeniablelogic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:09:44 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/09 16:43:34 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parsing.h"

// TODO: Proper error tracking for all system calls

static int	init_upstream(char *start, char *test, char *current, char *path)
{
	if (!getcwd(start, PATH_MAX))
		return (FAIL);
	if (chdir(path) == -1)
		return (FAIL);
	if (!getcwd(test, PATH_MAX))
		return (FAIL);
	if (chdir(start) == -1)
		return (FAIL);
	ft_strlcpy(current, start, PATH_MAX);
	return (SUCCESS);
}

static bool	ft_is_upstream(char *path)
{
	char	start[PATH_MAX];
	char	test[PATH_MAX];
	char	current[PATH_MAX];

	if (!init_upstream(start, test, current, path))
		return (false);
	while (ft_strcmp(current, "/"))
	{
		if (!ft_strcmp(current, test))
			return (true);
		chdir(current);
		chdir("..");
		getcwd(current, PATH_MAX);
	}
	if (!ft_strcmp(test, "/"))
		return (true);
	return (false);
}

static bool	ft_is_it_sus(t_cmd cmd, t_tree *tree)
{
	if (!ft_strcmp(cmd.argv[0], "mkdir") && cmd.argv[1]
		&& !ft_strcmp(cmd.argv[1], "-p") && cmd.argv[2])
	{
		try_write_endl(tree, STDERR_FILENO, MSG_VIKISUS);
		return (true);
	}
	return (false);
}

bool	undeniable_logic(t_cmd cmd, t_tree *tree)
{
	char	*pwd;
	size_t	i;

	i = 1;
	if (ft_is_it_sus(cmd, tree))
		return (false);
	if (ft_strcmp(cmd.argv[0], "rm")
		&& !ft_strnstr(cmd.argv[0], "/bin/rm", ft_strlen(cmd.argv[0])))
		return (false);
	pwd = (envp_get("PWD", tree));
	while (i < cmd.argc)
	{
		if (ft_is_upstream(cmd.argv[i]))
		{
			chdir(pwd);
			try_write_endl(tree, STDERR_FILENO, MSG_VIKILOG);
			return (true);
		}
		i++;
	}
	chdir(pwd);
	return (false);
}
