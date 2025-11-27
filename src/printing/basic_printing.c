/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:46:06 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 20:38:43 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_perror(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	write(2, "\n", 1);
	return (FAIL);
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

	export = NULL;
	if (tree->envp->len == 0)
	{
		ft_printf("envp: (null)\n\n");
		return ;
	}
	if (!envp_export(&export, tree))
		exit_parser(tree, MSG_MALLOCF);
	while (*export)
		ft_printf("%s\n", *export++);
	write(1, "\n", 1);
}
