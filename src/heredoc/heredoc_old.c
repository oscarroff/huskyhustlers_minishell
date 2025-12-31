/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_old.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:05:30 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 17:34:28 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parsing.h"
// #include "signals.h"
//
// static int	heredoc_init(char **delimiter, int *fd, t_token *tok, t_tree *tree)
// {
// 	// readline_signals_hook(TURN_OFF);
// 	// heredoc_signals_hook(TURN_ON);
// 	if (tok->quote_type == QUO_DEFAULT)
// 		tok->expand = true;
// 	if (!ft_superstrndup(delimiter, (char *)tok->tok_chars->data,
// 			tok->tok_chars->len, tree->a_buf))
// 		exit_parser(tree, MSG_MALLOCF);
// 	if (!vec_reset(tok->tok_chars))
// 		exit_parser(tree, MSG_UNINTAL);
// 	*fd = open("/tmp/heredoc_tmp",
// 			O_WRONLY | O_APPEND | O_CREAT | O_EXCL, FILE_ACCESS);
// 	if (*fd < 0)
// 		exit_parser(tree, MSG_OPENERR);
// 	return (SUCCESS);
// }
//
// static int	heredoc_reset(t_tree *tree, char **line)
// {
// 	(void)tree;
// 	g_receipt = 0;
// 	if (*line)
// 	{
// 		free(*line);
// 		*line = NULL;
// 	}
// 	return (SUCCESS);
// }
//
// static int	tokenise_heredoc(t_token *tok, int fd, t_tree *tree)
// {
// 	char	*line;
// 	t_vec	*tmp;
//
// 	if (close(fd) < 0)
// 		exit_parser(tree, MSG_ACCESSF);
// 	fd = open("/tmp/heredoc_tmp", O_RDONLY);
// 	if (fd < 0)
// 		exit_parser(tree, MSG_ACCESSF);
// 	tmp = NULL;
// 	if (!vec_new(tok->tok_chars, 1, sizeof(char))
// 		|| !vec_alloc(&tmp, tree->a_buf))
// 		exit_parser(tree, MSG_MALLOCF);
// 	while (1)
// 	{
// 		line = gnl(fd);
// 		if (!line)
// 		{
// 			vec_trim(tok->tok_chars, tok->tok_chars->len - 1, 1);
// 			free(line);
// 			return (SUCCESS);
// 		}
// 		if (!vec_from(tmp, line, ft_strlen(line), sizeof(char))
// 			|| !vec_append(tok->tok_chars, tmp))
// 			exit_parser(tree, MSG_MALLOCF);
// 		if (!vec_reset(tmp))
// 			exit_parser(tree, MSG_UNINTAL);
// 		free(line);
// 	}
// }
//
// static int	heredoc_exit(int fd, t_tree *tree)
// {
// 	if (fd)
// 		if (close(fd) < 0 || unlink("/tmp/heredoc_tmp") < 0)
// 			exit_parser(tree, MSG_ACCESSF);
// 	return (SUCCESS);
// }
//
// static int	ms_history_append(t_token *tok, char *line, t_tree *tree)
// {
// 	t_vec	*tmp_a;
// 	t_vec	*tmp_b;
// 	char	nl;
//
// 	tmp_a = NULL;
// 	tmp_b = NULL;
// 	nl = '\n';
// 	if (!vec_alloc(&tmp_a, tree->a_buf)
// 		|| !vec_alloc(&tmp_b, tree->a_buf)
// 		|| !vec_new(tmp_a, 0, sizeof(char))
// 		|| !vec_append(tmp_a, tok->tok_chars))
// 		exit_parser(tree, MSG_MALLOCF);
// 	if (line)
// 		if (!vec_push(tmp_a, &nl)
// 			|| !vec_from(tmp_b, line, ft_strlen(line), sizeof(char))
// 			|| !vec_append(tmp_a, tmp_b))
// 		exit_parser(tree, MSG_MALLOCF);
// 	if (!ft_superstrndup(&tok->heredoc, (char *)tmp_a->data,
// 		tmp_a->len, tree->a_buf))
// 		exit_parser(tree, MSG_MALLOCF);
// 	return (SUCCESS);
// }
//
// int	heredoc_clean_exit(t_token *tok, int fd, char *line, t_tree *tree)
// {
// 	if (!tokenise_heredoc(tok, fd, tree)
// 		|| !ms_history_append(tok, line, tree)
// 		|| !heredoc_reset(tree, &line)
// 		|| !heredoc_exit(fd, tree))
// 		return (FAIL);
// 	rl_clear_history();
// 	return (SUCCESS);
// }
//
// int	heredoc_dirty_exit(int fd, char *line, t_tree *tree)
// {
// 	heredoc_reset(tree, &line);
// 	heredoc_exit(fd, tree);
// 	rl_clear_history();
// 	return (SUCCESS);
// }
//
// int	heredoc(t_token *tok, t_tree *tree)
// {
// 	char	*line;
// 	char	*delimiter;
// 	int		fd;
//
// 	line = NULL;
// 	delimiter = NULL;
// 	fd = 0;
// 	if (!tok->tok_chars || !heredoc_init(&delimiter, &fd, tok, tree))
// 		return (FAIL);
// 	while (1)
// 	{
// 		heredoc_reset(tree, &line);
// 		line = readline("> ");
// 		if (g_receipt == EXIT_CTRLC)
// 			return (heredoc_dirty_exit(fd, line, tree));
// 		if (line && ft_strlen(line) == 0)
// 			continue ;
// 		else if (line == NULL || ft_strcmp(line, delimiter) == 0)
// 			return (heredoc_clean_exit(tok, fd, line, tree));
// 		ft_putendl_fd(line, fd);
// 	}
// }
