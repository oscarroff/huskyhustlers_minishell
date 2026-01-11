/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isambiguous.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:57:33 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/11 11:47:35 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_ambiguous_warn(char *src, char *warn);

bool	ft_isambiguous(char *env_key, const char *env_var, t_token *tok)
{
	size_t	space_flag;

	if (tok->type != TOK_IO)
		return (false);
	if (!env_var || ft_strlen(env_var) == 0)
	{
		ft_ambiguous_warn(env_key, MSG_AMBIGUO);
		return (true);
	}
	space_flag = 0;
	while (*env_var)
	{
		if (space_flag == 1 && !ft_isspace(*env_var) && tok->quote_char == '\0')
		{
			ft_ambiguous_warn(env_key, MSG_AMBIGUO);
			return (true);
		}
		if (ft_isspace(*env_var))
			space_flag = 1;
		env_var++;
	}
	return (false);
}

static int	ft_ambiguous_warn(char *src, char *warn)
{
	try_write(NULL, STDERR_FILENO, "minishell: ");
	if (src)
	{
		try_write(NULL, STDERR_FILENO, "$");
		try_write(NULL, STDERR_FILENO, src);
		try_write(NULL, STDERR_FILENO, ": ");
	}
	if (warn)
		try_write_endl(NULL, STDERR_FILENO, warn);
	else
		try_write_endl(NULL, STDERR_FILENO, "error undefined");
	return (FAIL);
}
