/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:05:30 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/22 15:56:37 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"
#include <fcntl.h>

static int	heredoc_init(char **delimiter, int *fd, t_token *tok, t_tree *tree)
{
	if (!ft_superstrndup(delimiter, (char *)tok->tok_chars->data,
		tok->tok_chars->len, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_reset(tok->tok_chars))
		exit_parser(tree, MSG_UNINTAL);
	*fd = open("/tmp/heredoc_tmp",
			O_WRONLY | O_APPEND | O_CREAT | O_EXCL, FILE_ACCESS);
	if (*fd < 0)
		exit_parser(tree, MSG_OPENERR);
	return (SUCCESS);
}

static int	heredoc_reset(t_tree *tree, char **line)
{
	(void)tree;
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (SUCCESS);
}

static int	tokenise_heredoc(t_token *tok, int fd, t_tree *tree)
{
	char	*line;
	t_vec	*tmp;

	if (close(fd) < 0)
		exit_parser(tree, MSG_ACCESSF);
	fd = open("/tmp/heredoc_tmp", O_RDONLY);
	if (fd < 0)
		exit_parser(tree, MSG_ACCESSF);
	tmp = NULL;
	if (!vec_new(tok->tok_chars, 1, sizeof(char))
		|| !vec_alloc(&tmp, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	while (1)
	{
		line = gnl(fd);
		if (!line)
		{
			vec_trim(tok->tok_chars, tok->tok_chars->len - 1, 1);
			free(line);
			return (SUCCESS);
		}
		if (!vec_from(tmp, line, ft_strlen(line), sizeof(char)))
			exit_parser(tree, MSG_MALLOCF);
		if (!vec_append(tok->tok_chars, tmp))
			exit_parser(tree, MSG_MALLOCF);
		if (!vec_reset(tmp))
			exit_parser(tree, MSG_UNINTAL);
		free(line);
	}
	return (SUCCESS);
}

static int	heredoc_exit(int fd, t_tree *tree)
{
	if (fd)
		if (close(fd) < 0 || unlink("/tmp/heredoc_tmp") < 0)
			exit_parser(tree, MSG_ACCESSF);
	return (SUCCESS);
}

int	heredoc(t_token *tok, t_tree *tree)
{
	char	*line;
	char	*delimiter;
	int		fd;

	line = NULL;
	delimiter = NULL;
	fd = 0;
	if (!tok->tok_chars || !heredoc_init(&delimiter, &fd, tok, tree))
		return (FAIL);
	while (1)
	{
		if (!heredoc_reset(tree, &line))
			return (FAIL);
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		{
			// ft_putchar_fd('\0', fd);
			if (!heredoc_reset(tree, &line)
				|| !tokenise_heredoc(tok, fd, tree)
				|| !heredoc_exit(fd, tree))
				return (FAIL);
			return (SUCCESS);
		}
		ft_putendl_fd(line, fd);
	}
}
