/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:27:49 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/05 11:27:50 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"
#include "../../inc/minishell.h"

static void	newline_option(size_t *idx, bool *is_newline, char **argv);

int	echo(t_exec *exec)
{
	size_t	i;
	bool	is_newline;
	bool	is_space;
	int		fd_out;

	fd_out = STDOUT_FILENO;
	if (exec->redir_out > 0)
		fd_out = exec->redir_out;
	i = 1;
	is_space = false;
	newline_option(&i, &is_newline, exec->cmd->argv);
	while (exec->cmd->argv[i])
	{
		if (is_space)
			try_write(exec->tree, fd_out, " ");
		try_write(exec->tree, fd_out, exec->cmd->argv[i]);
		if (!is_space)
			is_space = true;
		i++;
	}
	if (is_newline)
		try_write(exec->tree, fd_out, "\n");
	return (0);
}

static void	newline_option(size_t *idx, bool *is_newline, char **argv)
{
	size_t	j;
	size_t	i;

	i = *idx;
	*is_newline = true;
	if (argv[i] == NULL)
		return ;
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (argv[i] && argv[i][j] == 'n')
			j++;
		if (argv[i] && argv[i][j] != 'n' && argv[i][j] != '\0')
			break ;
		*is_newline = false;
		(*idx)++;
		i++;
	}
}
