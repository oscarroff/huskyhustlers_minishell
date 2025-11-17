/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:00:40 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/17 21:50:21 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

volatile sig_atomic_t	g_receipt;

static void	init_envp(t_tree *tree)
{
	if (!vec_alloc(&tree->envp, tree->arena))
		clean_exit(tree, MSG_MALLOCF);
	if (!vec_new(tree->envp, 0, sizeof(char *)))
		clean_exit(tree, MSG_MALLOCF);
}

void	fetch_envp(t_tree *tree, char **envp)
{
	char	*tmp;
	char	**test;
	size_t	i;

	tmp = NULL;
	test = NULL;
	i = 0;
	init_envp(tree);
	while (envp[i])
	{
		if (!ft_superstrdup(&tmp, envp[i], tree->arena))
			clean_exit(tree, MSG_MALLOCF);
		if (!vec_push(tree->envp, &tmp))
			clean_exit(tree, MSG_MALLOCF);
		tmp = NULL;
		i++;
	}
}
