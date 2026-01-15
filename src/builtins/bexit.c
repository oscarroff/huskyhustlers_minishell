/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:27:42 by jvalkama          #+#    #+#             */
/*   Updated: 2026/01/07 17:12:43 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"
#include "../../inc/minishell.h"

// TODO: Exit leads to wait_pids somehow.

static inline bool	is_valid_value(char *str, uint8_t *status);
static inline bool	is_numeric(char *str, int *i);

int	b_exit(t_exec *exec)
{
	uint8_t	exit_code;

	exit_code = exec->exec_status;
	if (exec->cmd->argv[1])
	{
		if (is_valid_value(exec->cmd->argv[1], &exit_code) == false)
			exec->exec_status = exe_err(exec, M_NUMARG, (int []){WARN, \
ERR_BTIN});
		else if (exec->cmd->argc > 2)
		{
			exec->exec_status = exe_err(exec, M_ARGC, (int []){WARN, ERR_GEN});
			return (ERR_GEN);
		}
	}
	clean(exec->tree);
	exit(exit_code);
}

static uint8_t	mega_atoi(char *str, uint8_t *exit_code)
{
	unsigned long long	res;
	int					sign;
	int					digit;

	res = 0;
	sign = 1;
	if (ft_issign((int)*str))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		digit = *str - '0';
		res = res * 10 + digit;
		if (res > LLONG_MAX)
		{
			*exit_code = ERR_BTIN;
			return (ERR_BTIN);
		}
		str++;
	}
	*exit_code = (uint8_t)(res * sign);
	return (0);
}

static inline bool	is_valid_value(char *str, uint8_t *exit_code)
{
	int	i;

	i = 0;
	if (is_numeric(str, &i) == false || !*str)
	{
		*exit_code = ERR_BTIN;
		return (false);
	}
	else
	{
		if (mega_atoi(str, exit_code) == ERR_BTIN)
			return (false);
	}
	return (true);
}

static inline bool	is_numeric(char *str, int *i)
{
	if (str[0] == '-' || str[0] == '+')
	{
		(*i)++;
		if (!str[*i])
			return (false);
	}
	while (str[*i])
	{
		if (ft_isdigit(str[*i]) == false)
			return (false);
		(*i)++;
	}
	return (true);
}
