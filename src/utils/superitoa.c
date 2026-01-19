/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:13:39 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/19 14:15:23 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_nbrcpy(char *num, int n, int sign, int nlen);
static int	ft_nbrsize(int n);
static int	ft_nbrsign(int *n);

int	ft_superitoa(char **num, int n, t_arena *arena)
{
	char	*tmp;
	int		nlen;
	int		sign;

	if (n == -2147483648)
		return (ft_superstrdup(&tmp, "-2147483648", arena));
	sign = ft_nbrsign(&n);
	nlen = ft_nbrsize(n);
	if (sign == -1)
		nlen += 1;
	if (arena)
	{
		if (!ft_arena_alloc(arena, (void **)&tmp, (nlen + 1) * sizeof(char)))
			return (FAIL);
	}
	else
	{
		tmp = malloc((nlen + 1) * sizeof(char));
		if (!tmp)
			return (FAIL);
	}
	ft_nbrcpy(tmp, n, sign, nlen);
	tmp[nlen] = '\0';
	*num = tmp;
	return (SUCCESS);
}

static int	ft_nbrsign(int *n)
{
	int	sign;

	if (*n < 0)
	{
		sign = -1;
		*n = -*n;
	}
	else
		sign = 1;
	return (sign);
}

static int	ft_nbrsize(int n)
{
	int	power;
	int	nlen;

	power = 1;
	nlen = 1;
	while (n / power > 9)
	{
		power *= 10;
		nlen += 1;
	}
	return (nlen);
}

static void	ft_nbrcpy(char *num, int n, int sign, int nlen)
{
	if (sign == -1)
		num[0] = '-';
	nlen -= 1;
	if (n > 9)
		ft_nbrcpy(num, n / 10, 1, nlen);
	num[nlen] = (n % 10) + '0';
}
