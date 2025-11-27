/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:46:33 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 21:00:16 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_badstring(char *line, int len)
{
	if (ft_strnstr(line, ">>>", len))
		return (ft_perror(MSG_SYX_GRE));
	if (ft_strnstr(line, "<<<", len))
		return (ft_perror(MSG_SYX_LES));
	if (ft_isstartpipe(line))
		return (ft_perror(MSG_SYX_PIP));
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

int	valid_input(char *line)
{
	size_t	len;
	size_t	i;
	char	quote;

	len = ft_strlen(line);
	i = 0;
	quote = '\0';
	if (!ft_badstring(line, len))
		return (FAIL);
	while (i < len)
	{
		ft_isquote(&quote, line[i]);
		if (ft_isredirect(line + i) && ft_missingio(line + i))
			return (ft_perror(MSG_SYX_ERR));
		if (line[i] == '$' && ft_isbadsub(line + i + 1)) // FIXME: Neccessary?
			return (ft_perror(MSG_BAD_SUB));
		if (line[i] == '|' && ft_isdblpipe(line + i))
			return (ft_perror(MSG_SYX_PIP));
		i++;
	}
	if (quote != '\0')
		return (ft_perror(MSG_OPENQUO));
	return (SUCCESS);
}
