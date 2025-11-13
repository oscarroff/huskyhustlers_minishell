/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:59:02 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 16:44:52 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static size_t	parse_exp(t_token *tok, t_vec *tmp, size_t i, t_tree *tree);
static size_t	exp_len(size_t *start, bool *braces, t_token *tok, size_t i);
static int		expand_env_var(t_vec *tmp, t_tree *tree);
static void		rm_exp(t_token *tok, size_t *start, size_t len, bool braces);

void	expandise(t_token *tok, t_tree *tree)
{
	t_vec	*tmp;
	size_t	i;

	tmp = NULL;
	i = 0;
	if (!vec_alloc(&tmp, tree->arena))
		clean_exit(tree, MSG_MALLOCF);
	while (i < tok->tok_chars->len)
	{
		if (((char *)tok->tok_chars->data)[i] == '$')
		{
			i += parse_exp(tok, tmp, i, tree);
			if (tmp->len > 0)
				vec_reset(tmp);
		}
		i++;
	}
}

static size_t	parse_exp(t_token *tok, t_vec *tmp, size_t i, t_tree *tree)
{
	size_t	start;
	size_t	len;
	bool	braces;

	start = 0;
	braces = false;
	len = exp_len(&start, &braces, tok, i);
	if (len == 0)
	{
		rm_exp(tok, &start, len, braces);
		return (0);
	}
	if (!vec_from(tmp, vec_get(tok->tok_chars, start),
			len + 1, sizeof(char)))
		clean_exit(tree, MSG_MALLOCF);
	tmp->data[len] = '\0';
	rm_exp(tok, &start, len, braces);
	if (!expand_env_var(tmp, tree))
		return (0);
	if (!vec_inpend(tok->tok_chars, tmp, start))
		clean_exit(tree, MSG_MALLOCF);
	return (tmp->len);
}

static size_t	exp_len(size_t *start, bool *braces, t_token *tok, size_t i)
{
	size_t	len;

	len = 0;
	if (((char *)tok->tok_chars->data)[i + 1] == '{')
	{
		i += 2;
		*braces = true;
	}
	else
		i += 1;
	while (i + len < tok->tok_chars->len
		&& ((char *)tok->tok_chars->data)[i + len] != '}'
		&& ((char *)tok->tok_chars->data)[i + len] != ' ')
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

static void	rm_exp(t_token *tok, size_t *start, size_t len, bool braces)
{
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
	vec_trim(tok->tok_chars, *start, len);
}
