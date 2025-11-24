/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:05:30 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 20:23:31 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"
#include <fcntl.h>
#include <readline/readline.h>

static int	heredoc_init(char **delimiter, int *fd, t_token *tok, t_tree *tree)
{
	if (tok->quote_type == QUO_DEFAULT)
		tok->expand = true;
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
	if (!vec_new(tok->tok_chars, 0, sizeof(char))
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

int	heredoc_clean_exit(t_token *tok, int fd, char *line, t_tree *tree)
{
	if (!tokenise_heredoc(tok, fd, tree)
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
		if (g_receipt == SIGINT)
			return (heredoc_dirty_exit(fd, line, tree));
		heredoc_reset(tree, &line);
		line = readline("> ");
		if (g_receipt == SIGINT)
			return (heredoc_dirty_exit(fd, line, tree));
		if (line && ft_strlen(line) == 0)
			continue ;
		else if (line == NULL || ft_strcmp(line, delimiter) == 0)
			return (heredoc_clean_exit(tok, fd, line, tree));
		ft_putendl_fd(line, fd);
	}
}
