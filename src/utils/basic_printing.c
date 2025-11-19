/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:46:06 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/17 21:45:18 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	print_debugging(t_vec *tokens, t_tree *tree)
{
	if (!tokens || !tree)
		return ;
	write(1, "\n", 1);
	print_tokens_vars(tokens);
	write(1, "\n", 1);
	print_cmd_tab(tree->cmd_tab);
	write(1, "\n", 1);
}

void	print_tokens(t_vec *tokens)
{
	t_token	*tok;
	size_t	i;

	if (!tokens)
		return ;
	write(1, "Tokens: ", 8);
	i = 0;
	while (i < tokens->len)
	{
		tok = *(t_token **)vec_get(tokens, i);
		write(1, "[", 1);
		write(1, (char *)tok->tok_chars->data, tok->tok_chars->len);
		write(1, "] ", 2);
		i++;
	}
	write(1, "\n", 1);
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

static void	print_io(char **array, char *name)
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
		i++;
	}
	write(1, "\n", 1);
}

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
		print_io(cmd->input, "input");
		print_io(cmd->output, "output");
		i++;
	}
}

void	print_envp(t_vec *envp)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!envp)
		return ;
	while (i < envp->len)
	{
		tmp = *(char **)vec_get(envp, i);
		ft_printf("%s\n", tmp);
		i++;
	}
}
