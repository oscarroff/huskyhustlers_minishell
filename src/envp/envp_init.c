/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:00:40 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 20:14:08 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

volatile sig_atomic_t	g_receipt;

static void	envp_vec_init(t_tree *tree);
static void	envp_key_value_init(t_keyval **dst, t_tree *tree);
static int	envp_key_value_parse(t_keyval **dst, char *src, t_tree *tree);

void	envp_init(t_tree *tree, char **envp)
{
	t_keyval	*tmp;
	size_t		i;

	tmp = NULL;
	i = 0;
	envp_vec_init(tree);
	while (envp[i])
	{
		if (!envp_key_value_parse(&tmp, envp[i], tree)
			|| !vec_push(tree->envp, &tmp))
			exit_parser(tree, MSG_MALLOCF);
		tmp = NULL;
		i++;
	}
}

static void	envp_vec_init(t_tree *tree)
{
	if (!ft_arena_init(&tree->a_sys, ARENA_BUF))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_alloc(&tree->envp, tree->a_sys)
		|| !vec_new(tree->envp, 0, sizeof(t_keyval *))
	)
		exit_parser(tree, MSG_MALLOCF);
}

static int	envp_key_value_parse(t_keyval **dst, char *src, t_tree *tree)
{
	t_keyval	*tmp;
	size_t		i;
	size_t		j;

	tmp = NULL;
	i = 0;
	if (!dst || !tree)
		return (FAIL);
	envp_key_value_init(&tmp, tree);
	while (src[i] && src[i] != '=')
		i++;
	if (!ft_superstrndup(&tmp->key, src, i, tree->a_sys))
		exit_parser(tree, MSG_MALLOCF);
	if (src[i] != '=')
		return (SUCCESS);
	i++;
	j = 0;
	while (src[i + j])
		j++;
	if (!ft_superstrndup(&tmp->value, src + i, j, tree->a_sys))
		exit_parser(tree, MSG_MALLOCF);
	*dst = tmp;
	return (SUCCESS);
}

static void	envp_key_value_init(t_keyval **dst, t_tree *tree)
{
	t_keyval	*new;

	new = NULL;
	if (!ft_arena_alloc(tree->a_sys, (void **)&new, sizeof(t_keyval)))
		exit_parser(tree, MSG_MALLOCF);
	new->key = NULL;
	new->value = NULL;
	*dst = new;
}
