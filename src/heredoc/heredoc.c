/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:05:30 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/15 16:59:17 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "messages.h"
#include "minishell.h"
#include "signals.h"
#include "parsing.h"

extern volatile sig_atomic_t	g_receipt;

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

static int	strip_quotes(t_token *tok, t_tree *tree)
{
	char	*tmp;
	size_t	i;

	tmp = (char *)tok->tok_chars->data;
	i = 0;
	while (i < tok->tok_chars->len)
	{
		if (tmp[i] == '"' || tmp[i] == '\'')
		{
			if (!vec_remove(tok->tok_chars, i))
				exit_parser(tree, MSG_MALLOCF);
		}
		else
			i++;
	}
	return (SUCCESS);
}

static int	heredoc_quotes(t_token *tok, t_tree *tree)
{
	char	*tmp;
	size_t	i;

	tmp = (char *)tok->tok_chars->data;
	i = 0;
	while (i < tok->tok_chars->len)
	{
		if (tmp[i] == '"' || tmp[i] == '\'')
		{
			if (tmp[i] == '"')
				tok->quote_type = QUO_DOUBLE;
			if (tmp[i] == '\'')
				tok->quote_type = QUO_SINGLE;
			break ;
		}
		i++;
	}
	if (!strip_quotes(tok, tree))
		return (FAIL);
	return (SUCCESS);
}

static int	heredoc_init(char **delimiter, int *fd, t_token *tok, t_tree *tree)
{
	char	*tmp;

	tmp = NULL;
	if (!heredoc_quotes(tok, tree))
		return (FAIL);
	if (!ft_superstrndup(&tmp, (char *)tok->tok_chars->data,
			tok->tok_chars->len, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_reset(tok->tok_chars))
		exit_parser(tree, MSG_UNINTAL);
	*fd = open("/tmp/heredoc_tmp",
			O_WRONLY | O_APPEND | O_CREAT | O_EXCL, FILE_ACCESS);
	if (*fd < 0)
		exit_parser(tree, MSG_OPENERR);
	*delimiter = tmp;
	readline_signals_init(TURN_OFF);
	heredoc_signals_init(TURN_ON);
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
