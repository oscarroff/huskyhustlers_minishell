/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:05:30 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/27 14:07:41 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	heredoc_init(char **delimiter, int *fd, t_token *tok, t_tree *tree);

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

int	heredoc_reset(t_tree *tree, char **line)
{
	(void)tree;
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (SUCCESS);
}
