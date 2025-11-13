/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:46:06 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 15:07:04 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	print_debugging(t_vec *tokens, t_tree *tree)
{
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

void	print_cmd_tab(t_vec *cmd_tab)
{
	t_cmd	*cmd;
	size_t	i;
size_t	j;

	i = 0;
	ft_printf("COMMAND TABLE\n");
	while (i < cmd_tab->len)
	{
		j = 0;
		cmd = *(t_cmd **)vec_get(cmd_tab, i);
		ft_printf("CMD %u\n", (uint32_t)i + 1);
		ft_printf("argc: %u ", (uint32_t)cmd->argc);
		while (j < cmd->argc)
		{
			ft_printf("argv[%u]: %s ", (uint32_t)j, cmd->argv[j]);
			j++;
		}
		ft_printf("\ninput: %s ouput: %s\n", cmd->input, cmd->output);
		i++;
	}
}
