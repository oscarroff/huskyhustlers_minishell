/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:46:06 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/19 22:03:43 by thblack-         ###   ########.fr       */
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
