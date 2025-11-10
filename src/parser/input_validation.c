/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:46:33 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/10 12:22:14 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parsing.h"

int	valid_input(char *line)
{
	size_t	len;
	size_t	i;
	char	quote;

	len = ft_strlen(line);
	i = 0;
	quote = '\0';
	if (ft_strnstr(line, ">>>", len))
		return (ft_perror(MSG_SYX_GRE));
	if (ft_strnstr(line, "<<<", len))
		return (ft_perror(MSG_SYX_LES));
	while (i < len)
	{
		ft_isquote(&quote, line[i]);
		if (line[i] == '|')
			if (ft_isdblpipe(line + i))
				return (ft_perror(MSG_SYX_PIP));
		i++;
	}
	if (quote != '\0')
		return (ft_perror(MSG_OPENQUO));
	return (OK);
}

int	ft_isquote(char *quote, int c)
{
	if ((c != '"' && c != '\'') || !quote)
		return (0);
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
	return (1);
}

int	ft_isdblpipe(char *line)
{
	size_t	i;

	i = 1;
	if (line[i] == '|')
		return (0);
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '|')
		return (1);
	return (0);
}
