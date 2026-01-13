/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:59:02 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/12 15:05:33 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "minishell.h"

static int		expand_parse(t_parse *p, t_vec *tmp, size_t *i, t_tree *tree);
static size_t	expand_len(t_token *tok, size_t i);
static int		expand_env_var(t_vec *tmp, t_parse *p, size_t i, t_tree *tree);
static int		expand_insert(t_parse *p, t_vec *tmp, size_t i, t_tree *tree);

int	expandise(t_parse *p, t_tree *tree)
{
	char	*src;
	t_vec	*tmp;
	size_t	i;
	size_t	old_rd;
	t_token	*working;

	if (!p->tok || !p->tok->tok_chars || p->tok->tok_chars->len == 0)
		return (SUCCESS);
	tmp = NULL;
	i = 0;
	old_rd = p->read_size;
	working = p->tok;
	if (!vec_alloc(&tmp, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	while (i + 1 < working->tok_chars->len)
	{
		src = (char *)working->tok_chars->data;
		ft_isquote(&working->quote_char, src[i]);
		if (src[i] == '$' && working->quote_char != '\''
			&& (ft_isalpha(src[i + 1]) || src[i + 1] == '_'))
		{
			if (!expand_parse(p, tmp, &i, tree))
				return (FAIL);
			vec_reset(tmp);
		}
		else
			i++;
		ft_printf("\ni: %u c: %c rd_s: %i\n", (uint32_t)i, src[i], (uint32_t)p->read_size);
		print_tokens_vars(p->tokens);
		ft_printf("len: %u\n", (uint32_t)working->tok_chars->len);
		ft_printf("vec size: %u\n", (uint32_t)p->tokens->len);
		vec_printf_s(working->tok_chars);
		ft_printf("\n");
	}
	working->quote_char = '\0';
	p->tok = working;
	p->read_size = old_rd + i;
	return (SUCCESS);
}

static int	expand_parse(t_parse *p, t_vec *tmp, size_t *i, t_tree *tree)
{
	size_t	len;
	char	null;
	t_token	*working;

	working = p->tok;
	len = expand_len(working, *i);
	null = '\0';
	if (len == 0)
	{
		if (!vec_trim(working->tok_chars, *i, 1))
			exit_parser(tree, MSG_MALLOCF);
		return (SUCCESS);
	}
	if (!vec_from(tmp, vec_get(working->tok_chars, *i + 1), len, sizeof(char))
		|| !vec_push(tmp, &null)
		|| !vec_trim(working->tok_chars, *i, len + 1))
		exit_parser(tree, MSG_MALLOCF);
	if (!expand_env_var(tmp, p, *i, tree))
		return (FAIL);
	printf("i: %zu exp_size: %zu\n", *i, p->exp_size);
	*i += p->exp_size;
	p->exp_size = 0;
	p->tok = working;
	return (SUCCESS);
}

static size_t	expand_len(t_token *tok, size_t i)
{
	char	*str;
	size_t	str_len;
	size_t	len;

	str = (char *)tok->tok_chars->data;
	str_len = tok->tok_chars->len;
	len = 1;
	if (i + len < str_len
		&& (ft_isalpha(str[i + len]) || str[i + len] == '_'))
		len++;
	while (i + len < str_len && ft_isalnum(str[i + len]))
		len++;
	return (len - 1);
}

static int	expand_env_var(t_vec *tmp, t_parse *p, size_t i, t_tree *tree)
{
	char	*env_key;
	char	*env_var;

	env_key = (char *)tmp->data;
	env_var = envp_get(env_key, tree);
	if (p->tok->type != TOK_IO && (!env_var || ft_strlen(env_var) == 0))
		return (SUCCESS);
	if (ft_isambiguous(env_key, env_var, p->tok, tree))
		return (FAIL);
	vec_reset(tmp);
	if (!vec_from(tmp, (void *)env_var, ft_strlen(env_var), sizeof(char)))
		exit_parser(tree, MSG_MALLOCF);
	if (!expand_insert(p, tmp, i, tree))
		return (FAIL);
	return (SUCCESS);
}

static int	expand_insert(t_parse *p, t_vec *tmp, size_t i, t_tree *tree)
{
	if (p->tok->quote_char == '"')
	{
		if (!vec_inpend(p->tok->tok_chars, tmp, i))
			exit_parser(tree, MSG_MALLOCF);
	}
	else if (p->tok->quote_char == '\0')
	{
		if (!go_back_around(p, tmp, i, tree))
			return (FAIL);
	}
	return (SUCCESS);
}
