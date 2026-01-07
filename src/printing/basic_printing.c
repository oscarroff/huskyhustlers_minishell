/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:46:06 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/07 14:36:01 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_ms_vars(t_tree *tree)
{
	ft_printf("GLOBAL VARIABLES\n");
	ft_printf("exit code: %d\n", tree->exit_code);
	ft_printf("shell level: %d\n", tree->ms_lvl);
	if (tree->pwd)
		ft_printf("pwd: %s\n", tree->pwd);
	else
		ft_printf("pwd: (null)");
}

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

void	print_envp(t_tree *tree)
{
	char	**export;
	size_t	i;

	print_ms_vars(tree);
	write(1, "\n", 1);
	export = NULL;
	if (tree->envp->len == 0)
	{
		ft_printf("envp: (null)\n\n");
		return ;
	}
	if (!envp_export(&export, tree))
		exit_parser(tree, MSG_MALLOCF);
	ft_printf("ENVP\n");
	i = 0;
	while (i < tree->envp->len)
		ft_printf("%s\n", export[i++]);
	write(1, "\n", 1);
}
