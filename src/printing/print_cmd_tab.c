/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:03:25 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 19:37:42 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static void	print_argv(char **array, char *name, size_t len);
static void	print_io(char **array, char *name, t_cmd *cmd);

void	print_cmd_tab(t_vec *cmd_tab)
{
	t_cmd	*cmd;
	size_t	i;

	if (!cmd_tab)
		return ;
	ft_printf("COMMAND TABLE\n");
	i = 0;
	while (i < cmd_tab->len)
	{
		cmd = *(t_cmd **)vec_get(cmd_tab, i);
		ft_printf("CMD %u\n", (uint32_t)i + 1);
		ft_printf("argc: %u ", (uint32_t)cmd->argc);
		print_argv(cmd->argv, "argv", cmd->argc);
		print_io(cmd->input, "input", cmd);
		print_io(cmd->output, "output", cmd);
		if (cmd->heredoc)
			ft_printf("heredoc: %s\n", cmd->heredoc);
		else
			ft_printf("heredoc: none\n");
		i++;
	}
}

static void	print_argv(char **array, char *name, size_t len)
{
	size_t	i;

	if (!array)
	{
		ft_printf("%s: none\n", name);
		return ;
	}
	i = 0;
	while (i < len && array[i])
	{
		ft_printf("%s[%u]: %s ", name, (uint32_t)i, array[i]);
		i++;
	}
	write(1, "\n", 1);
}

static void	print_io(char **array, char *name, t_cmd *cmd)
{
	size_t	i;

	if (!array)
	{
		ft_printf("%s: none\n", name);
		return ;
	}
	i = 0;
	while (array[i])
	{
		ft_printf("%s[%u]: %s ", name, (uint32_t)i, array[i]);
		if (!ft_strcmp(name, "output"))
		{
			if (cmd->out_type[i] == OUT_WRITE)
				ft_printf("OUT_WRITE ");
			if (cmd->out_type[i] == OUT_APPEND)
				ft_printf("OUT_APPEND ");
		}
		i++;
	}
	write(1, "\n", 1);
}
