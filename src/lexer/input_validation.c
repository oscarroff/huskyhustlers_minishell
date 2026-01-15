/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:46:33 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/07 15:42:28 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_badstring(char *line, int len, t_tree *tree)
{
	if (ft_strnstr(line, ">>>", len))
		return (ft_parse_warn(NULL, MSG_SYX_GRE, 2, tree));
	if (ft_strnstr(line, "<<<", len))
		return (ft_parse_warn(NULL, MSG_SYX_LES, 2, tree));
	if (ft_isstartpipe(line))
		return (ft_parse_warn(NULL, MSG_SYX_PIP, 2, tree));
	return (SUCCESS);
}

static bool	ft_isredirect(char *line)
{
	if (!line || !*line)
		return (false);
	if ((line[0] == '<' && (!line[1] || line[1] != '<'))
		|| (line[0] == '<' && (line[1] && line[1] == '<'))
		|| (line[0] == '>' && (!line[1] || line[1] != '>'))
		|| (line[0] == '>' && (line[1] && line[1] == '>')))
		return (true);
	return (false);
}

static bool	ft_missingio(char *line)
{
	char	rdr_char;

	if (!line || !*line)
		return (true);
	rdr_char = *line;
	while (*line && *line == rdr_char)
		line++;
	while (ft_isspace(*line))
		line++;
	if (!*line || ft_ismetachar(*line))
		return (true);
	return (false);
}

int	valid_input(char *line, t_tree *tree)
{
	size_t	len;
	size_t	i;
	char	quote;

	len = ft_strlen(line);
	i = 0;
	quote = '\0';
	if (!ft_badstring(line, len, tree))
		return (FAIL);
	while (i < len)
	{
		ft_isquote(&quote, line[i]);
		if (ft_isredirect(line + i) && ft_missingio(line + i))
			return (ft_parse_warn(NULL, MSG_SYX_ERR, 2, tree));
		if (line[i] == '|' && ft_isdblpipe(line + i))
			return (ft_parse_warn(NULL, MSG_SYX_PIP, 2, tree));
		i++;
	}
	if (quote != '\0')
		return (ft_parse_warn(NULL, MSG_OPENQUO, 2, tree));
	return (SUCCESS);
}
