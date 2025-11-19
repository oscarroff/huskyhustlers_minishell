/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:00:40 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/18 17:13:05 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

volatile sig_atomic_t	g_receipt;

static void	init_keyvalvec(t_tree *tree)
{
	if (!vec_alloc(&tree->envp, tree->arena)
		|| !vec_new(tree->envp, 0, sizeof(t_keyval *))
	)
		clean_exit(tree, MSG_MALLOCF);
}

static void	init_keyval(t_keyval **dst, t_tree *tree)
{
	t_keyval	*new;

	new = NULL;
	if (!ft_arena_alloc(tree->arena, (void **)&new, sizeof(t_keyval)))
		clean_exit(tree, MSG_MALLOCF);
	new->key = NULL;
	new->value = NULL;
	*dst = new;
}

static int	parse_envp_keyvalue(t_keyval **dst, char *src, t_tree *tree)
{
	t_keyval	*tmp;
	size_t		i;
	size_t		j;

	tmp = NULL;
	i = 0;
	if (!dst || !tree)
		return (FAIL);
	init_keyval(&tmp, tree);
	while (src[i] && src[i] != '=')
		i++;
	if (!ft_superstrndup(&tmp->key, src, i, tree->arena))
		clean_exit(tree, MSG_MALLOCF);
	if (src[i] != '=')
		return (SUCCESS);
	i++;
	j = 0;
	while (src[i + j])
		j++;
	if (!ft_superstrndup(&tmp->value, src + i, j, tree->arena))
		clean_exit(tree, MSG_MALLOCF);
	*dst = tmp;
	return (SUCCESS);
}

void	envp_init(t_tree *tree, char **envp, t_flag mode_flag)
{
	t_keyval	*tmp;
	char		**export;
	size_t		i;

	tmp = NULL;
	export = NULL;
	i = 0;
	init_keyvalvec(tree);
	while (envp[i])
	{
		if (!parse_envp_keyvalue(&tmp, envp[i], tree)
			|| !vec_push(tree->envp, &tmp))
			clean_exit(tree, MSG_MALLOCF);
		tmp = NULL;
		i++;
	}
	if (mode_flag == FLAG_ENVP)
	{
		write(1, "\n", 1);
		if (!envp_export(&export, tree))
			clean_exit(tree, MSG_MALLOCF);
		while (*export)
			ft_printf("%s\n", *export++);
		write(1, "\n", 1);
	}
}
