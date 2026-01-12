/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_input_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:44:49 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/11 11:39:19 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "messages.h"
#include "minishell.h"
#include "parsing.h"
#include <fcntl.h>

static int		ft_vecstrdup(char **dst, t_vec *src, t_tree *tree);
static int		try_access(char *path, int mode);

int	super_valid_input(t_tree *tree, t_vec *tokens)
{
	t_token	*tok;
	char	*path;
	size_t	i;

	if (!tree || !tokens)
		return (FAIL);
	path = NULL;
	i = 0;
	while (i < tokens->len)
	{
		tok = *(t_token **)vec_get(tokens, i);
		if (!tok)
			exit_parser(tree, MSG_ACCESSF);
		if (tok->type == TOK_IO && tok->redirect == RDR_READ)
		{
			if (!ft_vecstrdup(&path, tok->tok_chars, tree)
				|| !try_access(path, F_OK))
				return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

static int	ft_vecstrdup(char **dst, t_vec *src, t_tree *tree)
{
	char	*str;
	void	*tmp;
	size_t	len;

	if (!tree)
		return (FAIL);
	if (!src)
		return (SUCCESS);
	tmp = src->data;
	len = src->len;
	str = NULL;
	if (!ft_superstrndup(&str, tmp, len, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	str[len] = '\0';
	*dst = str;
	return (SUCCESS);
}

static int	try_access(char *path, int mode)
{
	if (access(path, mode) != 0)
	{
		errno = 0;
		ft_parse_warn(path, MSG_NO_FILE);
		return (FAIL);
	}
	return (SUCCESS);
}
