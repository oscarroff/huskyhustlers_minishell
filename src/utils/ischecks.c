/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ischecks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:53:07 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/10 12:46:23 by thblack-         ###   ########.fr       */
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

bool	ft_isquote(char *quote, int c)
{
	if ((c != '"' && c != '\'') || !quote)
		return (false);
	if (c == '"')
	{
		if (*quote == '\'')
			return (false);
		else if (*quote == '\0')
			*quote = '"';
		else if (*quote == '"')
			*quote = '\0';
	}
	if (c == '\'')
	{
		if (*quote == '"')
			return (false);
		else if (*quote == '\0')
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
