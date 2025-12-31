/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:03:15 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/27 14:09:13 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	heredoc_prep_exit(t_vec **tmp, t_token *tok, int fd, t_tree *tree);
static int	tokenise_heredoc(t_vec *tmp, t_token *tok, int fd, t_tree *tree);
static int	heredoc_exit(int fd, t_tree *tree);

int	heredoc_clean_exit(t_token *tok, int fd, char *line, t_tree *tree)
{
	t_vec	*tmp;

	tmp = NULL;
	if (!heredoc_prep_exit(&tmp, tok, fd, tree)
		|| !tokenise_heredoc(tmp, tok, fd, tree)
		|| !heredoc_reset(tree, &line)
		|| !heredoc_exit(fd, tree))
		return (FAIL);
	return (SUCCESS);
}

int	heredoc_dirty_exit(int fd, char *line, t_tree *tree)
{
	heredoc_reset(tree, &line);
	heredoc_exit(fd, tree);
	return (SUCCESS);
}

static int	heredoc_prep_exit(t_vec **tmp, t_token *tok, int fd, t_tree *tree)
{
	if (!vec_new(tok->tok_chars, 0, sizeof(char))
		|| !vec_alloc(tmp, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	if (close(fd) < 0)
		exit_parser(tree, MSG_ACCESSF);
	fd = open("/tmp/heredoc_tmp", O_RDONLY);
	if (fd < 0)
		exit_parser(tree, MSG_ACCESSF);
	return (SUCCESS);
}

static int	tokenise_heredoc(t_vec *tmp, t_token *tok, int fd, t_tree *tree)
{
	char	*line;

	while (1)
	{
		line = gnl(fd);
		if (!line)
		{
			vec_trim(tok->tok_chars, tok->tok_chars->len - 1, 1);
			free(line);
			return (SUCCESS);
		}
		if (!vec_from(tmp, line, ft_strlen(line), sizeof(char))
			|| !vec_append(tok->tok_chars, tmp))
			exit_parser(tree, MSG_MALLOCF);
		if (!vec_reset(tmp))
			exit_parser(tree, MSG_UNINTAL);
		free(line);
	}
}

static int	heredoc_exit(int fd, t_tree *tree)
{
	if (fd)
		if (close(fd) < 0 || unlink("/tmp/heredoc_tmp") < 0)
			exit_parser(tree, MSG_ACCESSF);
	return (SUCCESS);
}
