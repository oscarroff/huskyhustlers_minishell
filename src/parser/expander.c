/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:59:02 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/10 12:52:52 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"
#include <stdint.h>
#include <sys/types.h>

static size_t	parse_exp(t_token *token, t_vec *tmp, size_t i, t_tree *tree);
static size_t	exp_len(size_t *start, bool *braces, t_token *token, size_t i);
static int		expand_env_var(t_vec *tmp, t_tree *tree);
static void		rm_exp(t_token *token, size_t *start, size_t len, bool braces);

void	expandise(t_token *token, t_tree *tree)
{
	t_vec	*tmp;
	size_t	i;

	tmp = NULL;
	i = 0;
	if (!vec_alloc(&tmp, tree->arena))
		clean_exit(tree, MSG_MALLOCF);
	while (i < token->tok_chars->len)
	{
		if (((char *)token->tok_chars->data)[i] == '$')
		{
			i += parse_exp(token, tmp, i, tree);
			if (tmp->len > 0)
				vec_reset(tmp);
		}
		i++;
	}
}

static size_t	parse_exp(t_token *token, t_vec *tmp, size_t i, t_tree *tree)
{
	size_t	start;
	size_t	len;
	bool	braces;

	start = 0;
	braces = false;
	len = exp_len(&start, &braces, token, i);
	if (len == 0)
	{
		rm_exp(token, &start, len, braces);
		return (0);
	}
	if (!vec_from(tmp, vec_get(token->tok_chars, start),
			len + 1, sizeof(char)))
		clean_exit(tree, MSG_MALLOCF);
	tmp->data[len] = '\0';
	rm_exp(token, &start, len, braces);
	if (!expand_env_var(tmp, tree))
		return (0);
	if (!vec_inpend(token->tok_chars, tmp, start))
		clean_exit(tree, MSG_MALLOCF);
	return (tmp->len);
}

static size_t	exp_len(size_t *start, bool *braces, t_token *token, size_t i)
{
	size_t	len;

	len = 0;
	if (((char *)token->tok_chars->data)[i + 1] == '{')
	{
		i += 2;
		*braces = true;
	}
	else
		i += 1;
	while (i + len < token->tok_chars->len
		&& ((char *)token->tok_chars->data)[i + len] != '}'
		&& ((char *)token->tok_chars->data)[i + len] != ' ')
		len++;
	*start = i;
	return (len);
}

static int	expand_env_var(t_vec *tmp, t_tree *tree)
{
	char	*env_var;

	env_var = getenv((char *)tmp->data);
	if (!env_var)
		return (FAIL);
	vec_reset(tmp);
	if (!vec_from(tmp, env_var, ft_strlen(env_var), sizeof(char)))
		clean_exit(tree, MSG_MALLOCF);
	vec_pop(NULL, tmp);
	return (SUCCESS);
}

static void	rm_exp(t_token *token, size_t *start, size_t len, bool braces)
{
	size_t	i;

	i = 0;
	if (braces == true)
	{
		*start -= 2;
		len += 3;
	}
	else
	{
		*start -= 1;
		len += 1;
	}
	while (i < len)
	{
		vec_remove(token->tok_chars, *start);
		i++;
	}
}
