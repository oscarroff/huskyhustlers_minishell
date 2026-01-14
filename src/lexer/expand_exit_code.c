/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:11:24 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/14 14:47:19 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_nbrcpy(char *num, int n, int sign, int nlen)
{
	if (sign == -1)
		num[0] = '-';
	nlen -= 1;
	if (n > 9)
		ft_nbrcpy(num, n / 10, 1, nlen);
	num[nlen] = (n % 10) + '0';
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

int	expand_exit_code(t_vec *tmp, t_parse *p, size_t i, t_tree *tree)
{
	char	*num;

	num = NULL;
	if (!ft_superitoa(&num, tree->exit_code, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	vec_reset(tmp);
	if (!vec_from(tmp, num, ft_strlen(num), sizeof(char)))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_inpend(p->tok->tok_chars, tmp, i))
		exit_parser(tree, MSG_MALLOCF);
	return (SUCCESS);
}
