/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_var_verif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:57:19 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/15 16:57:52 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include <dirent.h>
#include <sys/stat.h>

static bool	is_in_directory(t_exec *exec, t_veri *verification);
static bool	fmatch(t_exec *exec, t_veri *v, struct stat *b, struct dirent *f);
static char	*gen_fullpath(t_exec *exec, t_veri *v, char *dir, char *file);
static void	clean_dirlist(char **dirlist);

bool	is_on_path_var(t_exec *exec, char *cmd_name, char *path_variable)
{
	t_veri	verification;
	char	**directory_list;
	size_t	i;

	i = 0;
	directory_list = ft_split(path_variable, ':');
	if (!directory_list)
	{
		exe_err(exec, MSG_MALLOCF, (int []){FATAL, EXIT_FAILURE});
	}
	verification.dirlist = directory_list;
	verification.cmd_name = cmd_name;
	while (directory_list[i])
	{
		verification.dir = directory_list[i];
		if (is_in_directory(exec, &verification))
		{
			clean_dirlist(directory_list);
			return (true);
		}
		i++;
	}
	clean_dirlist(directory_list);
	return (false);
}

static bool	is_in_directory(t_exec *exec, t_veri *verification)
{
	DIR				*dirstream;
	struct dirent	*file;
	struct stat		buffer;

	ft_memset(&buffer, 0, sizeof(buffer));
	dirstream = opendir(verification->dir);
	if (!dirstream)
		return (false);
	file = readdir(dirstream);
	while (file)
	{
		if (fmatch(exec, verification, &buffer, file))
		{
			closedir(dirstream);
			return (true);
		}
		file = readdir(dirstream);
	}
	closedir(dirstream);
	return (false);
}

static bool	fmatch(t_exec *exec, t_veri *v, struct stat *b, struct dirent *f)
{
	char	*full_path;

	full_path = gen_fullpath(exec, v, v->dir, v->cmd_name);
	stat(full_path, b);
	if (S_ISREG(b->st_mode))
	{
		if (ft_strcmp(f->d_name, v->cmd_name) == 0)
		{
			exec->extern_cmd_path = full_path;
			return (true);
		}
	}
	return (false);
}

static char	*gen_fullpath(t_exec *exec, t_veri *v, char *dir, char *file)
{
	size_t	len;
	size_t	i;
	char	*full_path;

	i = 0;
	len = ft_strlen(dir) + ft_strlen(file) + 2;
	if (ft_arena_alloc(exec->tree->a_buf, (void **)&full_path, len))
	{
		while (*dir && i < len)
			full_path[i++] = *dir++;
		full_path[i++] = '/';
		while (*file && i < len)
			full_path[i++] = *file++;
		full_path[i] = '\0';
		return (full_path);
	}
	else
	{
		clean_dirlist(v->dirlist);
		exe_err(exec, MSG_MALLOCF, (int []){FATAL, EXIT_FAILURE});
	}
	return (NULL);
}

static void	clean_dirlist(char **dirlist)
{
	size_t	i;

	i = 0;
	while (dirlist[i])
	{
		free(dirlist[i]);
		i++;
	}
	free(dirlist);
}
