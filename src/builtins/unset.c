/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:28:04 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/05 11:28:07 by jvalkama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

int	unset(t_exec *exec)
{
	char	**args;
	char	*arg;

	args = exec->cmd->argv + 1;
	while (*args)
	{
		arg = *args;
		if (envp_unset(exec->tree, arg) == FAIL)
			clean_exit(exec->tree, NULL);
		args++;
	}
	return (0);
}
