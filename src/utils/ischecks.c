/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ischecks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:53:07 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 20:36:22 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_ismetachar(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

bool	ft_isbadsub(char *line)
{
	(void)line;
	return (false);
	// if (!*line || *line == '$' || *line == '?' || ft_isspace(*line))
	// 	return (false);
	// if (!ft_isalpha(*line) && *line != '_')
	// 	return (true);
	// line++;
	// while (*line && (*line != '$' || ft_isspace(*line)))
	// {
	// 	if (!ft_isalnum(*line))
	// 		return (true);
	// 	line++;
	// }
	// return (false);
}

bool	ft_isquote(char *quote, int c)
{
	if ((c != '"' && c != '\'') || !quote)
		return (false);
	if (c == '"')
	{
		if (*quote == '\0')
			*quote = '"';
		else if (*quote == '"')
			*quote = '\0';
	}
	if (c == '\'')
	{
		if (*quote == '\0')
			*quote = '\'';
		else if (*quote == '\'')
			*quote = '\0';
	}
	return (true);
}

bool	ft_isstartpipe(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line == '|')
		return (true);
	return (false);
}

bool	ft_isdblpipe(char *line)
{
	size_t	i;

	i = 1;
	if (line[i] == '|')
		return (false);
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '|')
		return (true);
	return (false);
}
