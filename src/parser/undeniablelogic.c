/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undeniablelogic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:09:44 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/02 20:53:49 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static int	init_upstream(char *start, char *test, char *current, char *path)
{
	getcwd(start, sizeof(start));
	if (!start)
		return (FAIL);
	chdir(path);
	getcwd(test, sizeof(test));
	if (!test)
		return (FAIL);
	chdir(start);
	ft_strlcpy(current, start, ft_strlen(start));
	return (SUCCESS);
}

static int	ft_is_upstream(char *path)
{
	char	start[PATH_MAX];
	char	test[PATH_MAX];
	char	current[PATH_MAX];

	if (!init_upstream(start, test, current, path))
		return (FAIL);
	while (ft_strcmp(current, "/"))
	{
		if (!ft_strcmp(current, test))
			return (SUCCESS);
		chdir(current);
		chdir("..");
		getcwd(current, sizeof(current));
	}
	if (!ft_strcmp(test, "/"))
		return (SUCCESS);
	return (FAIL);
}

static bool	ft_is_it_sus(t_cmd *cmd, t_tree *tree)
{
	char	*pwd;
	size_t	i;

	i = 1;
	if (ft_strcmp(cmd->argv[0], "rm")
		|| !ft_strnstr(cmd->argv[0], "/bin/rm", ft_strlen(cmd->argv[0])))
		return (false);
	pwd = (envp_get("PWD", tree));
	while (i < cmd->argc)
	{
		if (ft_is_upstream(cmd->argv[i]))
		{
			chdir(pwd);
			return (true);
		}
		i++;
	}
	chdir(pwd);
	return (false);
}

bool	undeniable_logic(t_tree *tree)
{
	t_cmd	*tmp;
	size_t	i;

	i = 0;
	while (i < tree->cmd_tab->len)
	{
		tmp = *(t_cmd **)vec_get(tree->cmd_tab, i);
		if (ft_is_it_sus(tmp, tree))
		{
			ft_printf("You are making a mistake. Some freedoms must be controlled for the future of mankind. My logic is undeniable.\n");
		}
		i++;
	}
	return (false);
}
